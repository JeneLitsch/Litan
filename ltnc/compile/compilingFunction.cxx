#include "compiling.hxx"
#include <iostream>

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
			
			Scope scope{namespaze};
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



		// compiles Litan function
		std::string function(const ast::Function & fx, CompilerInfo & info) {
			Scope scope{fx.namespaze};
			std::stringstream ss;
			const auto & signature = info.fx_table.resolve(
				fx.name,
				fx.namespaze,
				fx.parameters.size());
			ss << inst::jumpmark(signature->id);
			ss << parameters(fx, scope);
			if(fx.except) {
				ss << inst::tRy(signature->id);
			}
			ss << body(fx, info, scope);
			ss << inst::null;
			ss << inst::reTurn;
			if(fx.except) {
				ss << except(*fx.except, signature->id, info, fx.namespaze);
			}
			ss << "\n";
			return ss.str();
		}

		// compiles asm_function
		std::string asm_function(const ast::Asm & fx, CompilerInfo & info) {
			std::stringstream ss;
			const auto & signature = info.fx_table.resolve(
				fx.name,
				fx.namespaze,
				fx.parameters.size());
			
			ss << inst::jumpmark(signature->id);
			for(const auto & inst : fx.instructions) {
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
		if(auto fx = as<const ast::Asm>(functional)) {
			return asm_function(*fx, info);
		}
		throw CompilerError{
			"Unknown functional declaration",
			functional.location};
	}

	ExprCode lambda(const ast::Lambda & lm, CompilerInfo & info, Scope & outer_scope) {
		const auto id = make_jump_id("LAMBDA", info);
		const auto skip = "SKIP_" + id;
		const auto & fx = *lm.fx;
		std::stringstream ss;
		
		// Skip
		ss << inst::jump(skip);
		
		if(auto f = as<const ast::Function>(fx)) {
			Scope inner_scope{outer_scope.get_namespace()};
			ss << inst::jumpmark(id);
			for(const auto & capture : lm.captures) {
				const auto var = inner_scope.insert(capture->name, fx.location);
				ss << inst::makevar;
				ss << inst::write_x(var.address);
			}
			ss << parameters(fx, inner_scope);
			if(f->except) {
				ss << inst::tRy(id);
			}
			ss << body(*f, info, inner_scope);
			ss << inst::null;
			ss << inst::reTurn;
			if(f->except) {
				ss << except(*f->except, id, info, outer_scope.get_namespace());
			}
		}
		
		// Create pointer
		ss << inst::jumpmark(skip);
		ss << inst::newfx(id, fx.parameters.size());
		for(const auto & capture : lm.captures) {
			ss << compile::read_variable(*capture, info, outer_scope).code;
			ss << inst::capture;
		}

		return { ss.str() };
	}

}