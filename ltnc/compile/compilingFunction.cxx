#include "compiling.hxx"
#include <iostream>

namespace ltn::c::compile {
	namespace {

		std::string parameters(const ast::Functional & fx, Scope & scope) {
			std::stringstream ss;
			auto params = fx.parameters;
			std::reverse(params.begin(), params.end());
			for(const auto & param : params) {
				const auto var = scope.insert(param, fx.debugInfo.line);
				ss << inst::makevar;
				ss << inst::write_x(var.address);
			}
			return ss.str();
		}

		std::string body(
			const ast::Function & fx,
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

		// compiles Litan function
		std::string function(const ast::Function & fx, CompilerInfo & info) {
			Scope scope{fx.nameSpace};
			std::stringstream ss;
			const auto & fxSig = info.fxTable.resolve(
				fx.name,
				fx.nameSpace,
				fx.parameters.size());
			ss << inst::jumpmark(fxSig->id);
			ss << parameters(fx, scope);
			ss << body(fx, info, scope);
			ss << inst::null;
			ss << inst::reTurn;
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
			functional.debugInfo.line};
	}

	ExprCode lambda(const ast::Lambda & lm, CompilerInfo & info, Scope & outerScope) {
		const auto id = makeJumpId("LAMBDA", info);
		const auto skip = "SKIP_" + id;
		const auto & fx = *lm.fx;
		std::stringstream ss;
		
		// Skip
		ss << inst::jump(skip);
		
		{ // Function
			Scope innerScope{outerScope.getNamespace()};
			ss << inst::jumpmark(id);
			for(const auto & capture : lm.captures) {
				const auto var = innerScope.insert(capture->name, fx.debugInfo.line);
				ss << inst::makevar;
				ss << inst::write_x(var.address);
			}
			ss << parameters(fx, innerScope);
			if(auto f = as<const ast::Function>(fx)) {
				ss << body(*f, info, innerScope);
			}
			ss << inst::null;
			ss << inst::reTurn;
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