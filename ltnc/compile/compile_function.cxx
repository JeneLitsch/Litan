#include "compile.hxx"
#include <iostream>
#include "build_in/build_in.hxx"

namespace ltn::c::compile {
	namespace {

		std::string parameters(const ast::Functional & fx, Scope & scope) {
			for(const auto & param : fx.parameters) {
				scope.insert(param, fx.location);
			}
			return inst::parameters(fx.parameters.size());
		}



		std::string body(
			const auto & fx,
			CompilerInfo & info,
			Scope & scope) {
			std::stringstream ss;
			if(fx.body) {
				const auto body = compile::statement(*fx.body, info, scope);
				for(std::size_t i = 0; i < body.var_count; i++) {
					ss << inst::makevar;
				}
				ss << body.code;
			}
			return ss.str();
		}



		std::string except(	
			const ast::Except & except,
			const std::string & fxid,
			CompilerInfo & info,
			const auto & namespaze) {
			
			Scope scope{namespaze, false};
			scope.insert(except.errorname, except.location);
			// std::cout << "ERR " << except.errorname << ":" << var.address << ":" << scope.recSize() << std::endl;
			std::ostringstream ss;
			ss << inst::jumpmark_except(fxid);
			ss << inst::parameters(1);
			ss << body(except, info, scope);
			ss << inst::null;
			ss << inst::reTurn;
			return ss.str();
		}

		namespace {
			// compiles Litan function
			std::string function(
				const ast::Function & fx,
				CompilerInfo & info,
				Scope & scope,
				std::optional<const std::string_view> capture) {
				
				std::stringstream ss;
				
				ss << inst::jumpmark(fx.id);
				if(capture) ss << *capture;
				ss << parameters(fx, scope);
				if(fx.except) ss << inst::tRy(fx.id);
				ss << body(fx, info, scope);
				ss << inst::null;
				ss << inst::reTurn;
				if(fx.except) ss << except(*fx.except, fx.id, info, fx.namespaze);
				ss << "\n";
				return ss.str();
			}
		}


		// compiles Litan function
		std::string function(const ast::Function & fx, CompilerInfo & info) {
			Scope scope{fx.namespaze, fx.c0nst};
			return function(fx, info, scope, std::nullopt);
		}



		// compiles asm_function
		std::string build_in_function(const ast::BuildIn & fx, CompilerInfo & info) {
			std::stringstream ss;
			const auto * signature = info.fx_table.resolve(
				fx.name,
				fx.namespaze,
				fx.parameters.size());
			
			ss << inst::jumpmark(signature->id);
			const auto instructions = resolve_build_in(fx.key);
			for(const auto & inst : instructions) {
				ss << inst << "\n";
			}
			ss << inst::null;
			ss << inst::reTurn;
			ss << "\n";
			return ss.str();
		}
	}



	// compiles functional node
	std::string functional(
		const ast::Functional & functional,
		CompilerInfo & info) {
		if(auto fx = as<const ast::Function>(functional)) {
			return function(*fx, info);
		}
		if(auto fx = as<const ast::BuildIn>(functional)) {
			return build_in_function(*fx, info);
		}
		throw CompilerError{
			"Unknown functional declaration",
			functional.location};
	}



	ExprCode lambda(const ast::Lambda & lm, CompilerInfo & info, Scope & outer_scope) {
		const auto & fx = *lm.fx;
		std::stringstream ss;
		
		// Skip
		ss << inst::jump(fx.id + "SKIP");
		
		// load captures
		Scope inner_scope{outer_scope.get_namespace(), fx.c0nst};
		std::ostringstream ss_capture;
		for(const auto & capture : lm.captures) {
			const auto var = inner_scope.insert(capture->name, fx.location);
			ss_capture << inst::makevar;
			ss_capture << inst::write_x(var.address);
		}

		// compile function
		ss << function(*lm.fx, info, inner_scope, ss_capture.str());

		// Create function pointer
		ss << inst::jumpmark(fx.id + "SKIP");
		ss << inst::newfx(fx.id, fx.parameters.size());
		
		// store captures
		for(const auto & capture : lm.captures) {
			ss << compile::read_variable(*capture, info, outer_scope).code;
			ss << inst::capture;
		}

		return { ss.str() };
	}

}