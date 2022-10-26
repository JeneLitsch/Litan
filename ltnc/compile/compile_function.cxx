#include "compile.hxx"
#include <iostream>
#include "build_in/build_in.hxx"
#include "ltnc/print/print.hxx"

namespace ltn::c {
	namespace {

		inst::Inst parameters(const ast::Functional & fx, Scope & scope) {
			for(const auto & param : fx.parameters) {
				scope.insert(param.name, fx.location, param.type);
			}
			return inst::parameters(static_cast<std::uint8_t>(fx.parameters.size()));
		}


		const std::string jumpmark_except(const std::string_view name) {
			std::stringstream ss;
			ss << "_" << name << "_EXCEPT";
			return ss.str(); 
		}

		const std::string jumpmark_skip(const std::string_view name) {
			std::stringstream ss;
			ss << "_" << name << "_SKIP";
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
					buf << inst::makevar();
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
			
			MajorScope scope{namespaze, false};
			scope.insert(except.errorname, except.location);
			// std::cout << "ERR " << except.errorname << ":" << var.address << ":" << scope.recSize() << std::endl;
			InstructionBuffer buf;
			buf << inst::label(jumpmark_except(fxid));
			buf << inst::parameters(1);
			buf << compile_body(except, info, scope);
			buf << inst::null();
			buf << inst::retvrn();
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
				
				buf << inst::label(fx.id);
				buf << capture;
				buf << parameters(fx, scope);
				if(fx.except) buf << inst::trY(jumpmark_except(fx.id));
				buf << compile_body(fx, info, scope);
				buf << inst::null();
				buf << inst::retvrn();
				if(fx.except) buf << compile_except(*fx.except, fx.id, info, fx.namespaze);
				
				return buf;
			}
		}



		// compiles Litan function
		InstructionBuffer compile_function(const ast::Function & fx, CompilerInfo & info) {
			MajorScope scope { fx.namespaze, fx.c0nst, fx.return_type };
			return compile_function(fx, info, scope, {});
		}



		// compiles asm_function
		InstructionBuffer compile_build_in_function(const ast::BuildIn & fx, CompilerInfo & info) {
			InstructionBuffer buf;
			const auto * signature = info.fx_table.resolve(
				fx.name,
				fx.namespaze,
				fx.parameters.size());
			
			buf << inst::label(signature->id);
			const auto body = resolve_build_in(fx.key); 
			buf << body;
			buf << inst::null();
			buf << inst::retvrn();
			
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



	ExprResult compile_lambda(const ast::Lambda & lm, CompilerInfo & info, Scope & outer_scope) {
		const auto & fx = *lm.fx;
		InstructionBuffer buf;
		
		// Skip
		buf << inst::jump(jumpmark_skip(fx.id));
		
		// load captures
		MajorScope inner_scope {
			outer_scope.get_namespace(),
			fx.c0nst };
		
		InstructionBuffer capture_buf;
		
		for(const auto & capture : lm.captures) {
			const auto var = inner_scope.insert(capture->name, fx.location);
			capture_buf << inst::makevar();
			capture_buf << inst::write_x(var.address);
		}

		// compile function
		buf << compile_function(*lm.fx, info, inner_scope, capture_buf);

		// Create function pointer
		buf << inst::label(jumpmark_skip(fx.id));
		buf << inst::newfx(fx.id, fx.parameters.size());
		
		// store captures
		for(const auto & capture : lm.captures) {
			buf << compile_read_variable(*capture, info, outer_scope).code;
			buf << inst::capture();
		}


		std::vector<type::Type> parameter_types;
		for(const auto & parameter : fx.parameters) {
			parameter_types.push_back(parameter.type);
		}

		return {
			.code = buf,
			.deduced_type = type::FxPtr {
				.return_type = fx.return_type,
				.parameter_types = parameter_types, 
			}
		};
	}
}