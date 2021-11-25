#include "compiling.hxx"

namespace ltn::c::compile {
	namespace {
		// compiles Litan function
		std::string function(const ast::Function & fx, CompilerInfo & info) {
			Scope scope{fx.nameSpace};
			std::stringstream ss;
			const auto & fxSig = info.fxTable.resolve(
				fx.name,
				fx.nameSpace,
				fx.parameters.size());
			ss << inst::jumpmark(fxSig->id);
			auto params = fx.parameters;
			std::reverse(params.begin(), params.end());
			for(const auto & param : params) {
				const auto addr = scope.insert(param, fx.debugInfo.line);
				ss << inst::makevar;
				ss << inst::addr(addr);
				ss << inst::write;
			}
			if(fx.body) {
				ss << compile::statement(*fx.body, info, scope).code;
			}
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
			for(const auto inst : fx.instructions) {
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
}