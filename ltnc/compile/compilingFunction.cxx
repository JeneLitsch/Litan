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
				for(std::size_t i = 0; i < body.varCount; i++) {
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
			Scope & scope) {
			
			const auto var = scope.insert(except.errorname, except.location);
			// std::cout << "ERR " << except.errorname << ":" << var.address << ":" << scope.recSize() << std::endl;
			std::ostringstream ss;
			ss << inst::jumpmarkExcept(fxid);
			ss << inst::c4tch;
			ss << inst::parameters(1);
			ss << body(except, info, scope);
			ss << inst::null;
			ss << inst::reTurn;
			return ss.str();
		}



		// compiles Litan function
		std::string function(const ast::Function & fx, CompilerInfo & info) {
			Scope scope{fx.nameSpace};
			std::stringstream ss;
			const auto & fxSig = info.fxTable.resolve(
				fx.name,
				fx.nameSpace,
				fx.parameters.size());
			ss << inst::jumpmark(fxSig->id);
			if(fx.except) {
				ss << inst::tRy(fxSig->id);
			}
			ss << parameters(fx, scope);
			ss << body(fx, info, scope);
			ss << inst::null;
			ss << inst::reTurn;
			if(fx.except) {
				// std::cout << "Size: " << scope.recSize() << std::endl;
				ss << except(*fx.except, fxSig->id, info, scope);
			}
			ss << "\n";
			return ss.str();
		}

		// compiles asmFunction
		std::string asmFunction(const ast::Asm & fx, CompilerInfo & info) {
			std::stringstream ss;
			const auto & fxSig = info.fxTable.resolve(
				fx.name,
				fx.nameSpace,
				fx.parameters.size());
			
			ss << inst::jumpmark(fxSig->id);
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
			return asmFunction(*fx, info);
		}
		throw CompilerError{
			"Unknown functional declaration",
			functional.location};
	}

	ExprCode lambda(const ast::Lambda & lm, CompilerInfo & info, Scope & outerScope) {
		const auto id = makeJumpId("LAMBDA", info);
		const auto skip = "SKIP_" + id;
		const auto & fx = *lm.fx;
		std::stringstream ss;
		
		// Skip
		ss << inst::jump(skip);
		
		if(auto f = as<const ast::Function>(fx)) {
			Scope innerScope{outerScope.getNamespace()};
			ss << inst::jumpmark(id);
			if(f->except) {
				ss << inst::tRy(id);
			}
			for(const auto & capture : lm.captures) {
				const auto var = innerScope.insert(capture->name, fx.location);
				ss << inst::makevar;
				ss << inst::write_x(var.address);
			}
			ss << parameters(fx, innerScope);
			ss << body(*f, info, innerScope);
			ss << inst::null;
			ss << inst::reTurn;
			if(f->except) {
				ss << except(*f->except, id, info, innerScope);
			}
		}
		
		// Create pointer
		ss << inst::jumpmark(skip);
		ss << inst::newfx(id, fx.parameters.size());
		for(const auto & capture : lm.captures) {
			ss << compile::readVar(*capture, info, outerScope).code;
			ss << inst::capture;
		}

		return { ss.str() };
	}

}