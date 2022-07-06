#include "compile.hxx"
#include <iostream>
#include "build_in/build_in.hxx"
#include "ltnc/print/print.hxx"

namespace ltn::c {
	namespace {

		ltn::inst::Instruction parameters(const ast::Functional & fx, Scope & scope) {
			for(const auto & param : fx.parameters) {
				scope.insert(param, fx.location);
			}
			return ltn::inst::Params{ static_cast<std::uint8_t>(fx.parameters.size()) };
		}


		const std::string jumpmark_except(const std::string_view name) {
			std::stringstream ss;
			ss << name << "_EXCEPT\n";
			return ss.str(); 
		}


		InstructionBuffer compile_body(
			const auto & fx,
			CompilerInfo & info,
			Scope & scope) {
			InstructionBuffer buf;
			if(fx.body) {
				const auto body = compile_statement(*fx.body, info, scope);
				for(std::size_t i = 0; i < body.var_count; i++) {
					buf << ltn::inst::Makevar{};
				}
				buf << body.code;
			}
			return buf;
		}



		InstructionBuffer compile_except(	
			const ast::Except & except,
			const std::string & fxid,
			CompilerInfo & info,
			const auto & namespaze) {
			
			Scope scope{namespaze, false};
			scope.insert(except.errorname, except.location);
			// std::cout << "ERR " << except.errorname << ":" << var.address << ":" << scope.recSize() << std::endl;
			InstructionBuffer buf;
			buf << ltn::inst::Label{jumpmark_except(fxid)};
			buf << ltn::inst::Params{1};
			buf << compile_body(except, info, scope);
			buf << ltn::inst::Null{};
			buf << ltn::inst::Return{};
			return buf;
		}



		namespace {
			// compiles Litan function
			InstructionBuffer compile_function(
				const ast::Function & fx,
				CompilerInfo & info,
				Scope & scope,
				InstructionBuffer capture) {
				
				InstructionBuffer buf;
				
				buf << ltn::inst::Label{fx.id};
				buf << capture;
				buf << parameters(fx, scope);
				if(fx.except) buf << ltn::inst::Try{jumpmark_except(fx.id)};
				buf << compile_body(fx, info, scope);
				buf << ltn::inst::Null{};
				buf << ltn::inst::Return{};
				if(fx.except) buf << compile_except(*fx.except, fx.id, info, fx.namespaze);
				
				return buf;
			}
		}


		// compiles Litan function
		InstructionBuffer compile_function(const ast::Function & fx, CompilerInfo & info) {
			Scope scope{fx.namespaze, fx.c0nst};
			return compile_function(fx, info, scope, {});
		}



		// compiles asm_function
		InstructionBuffer compile_build_in_function(const ast::BuildIn & fx, CompilerInfo & info) {
			InstructionBuffer buf;
			const auto * signature = info.fx_table.resolve(
				fx.name,
				fx.namespaze,
				fx.parameters.size());
			
			buf << ltn::inst::Label{signature->id};
			const auto body = resolve_build_in(fx.key); 
			buf << body;
			buf << ltn::inst::Null{};
			buf << ltn::inst::Return{};
			
			return buf;
		}
	}



	// compiles functional node
	InstructionBuffer compile_functional(
		const ast::Functional & functional,
		CompilerInfo & info) {
		if(auto fx = as<const ast::Function>(functional)) {
			return compile_function(*fx, info);
		}
		if(auto fx = as<const ast::BuildIn>(functional)) {
			return compile_build_in_function(*fx, info);
		}
		throw CompilerError{
			"Unknown functional declaration",
			functional.location};
	}



	ExprCode compile_lambda(const ast::Lambda & lm, CompilerInfo & info, Scope & outer_scope) {
		const auto & fx = *lm.fx;
		InstructionBuffer buf;
		
		// Skip
		buf << ltn::inst::Jump{fx.id + "SKIP"};
		
		// load captures
		Scope inner_scope{outer_scope.get_namespace(), fx.c0nst};
		InstructionBuffer capture_buf;
		for(const auto & capture : lm.captures) {
			const auto var = inner_scope.insert(capture->name, fx.location);
			capture_buf << ltn::inst::Makevar{};
			capture_buf << ltn::inst::Writex{var.address};
		}

		// compile function
		buf << compile_function(*lm.fx, info, inner_scope, capture_buf);

		// Create function pointer
		buf << ltn::inst::Label{fx.id + "SKIP"};
		buf << ltn::inst::Newfx{fx.id, fx.parameters.size()};
		
		// store captures
		for(const auto & capture : lm.captures) {
			buf << compile_read_variable(*capture, info, outer_scope).code;
			buf << ltn::inst::Capture{};
		}

		return { buf };
	}

}