#include "compile.hxx"
namespace ltn::c::compile {
	// compiles -> return...;
	StmtCode reTurn(const ast::Return & ret, CompilerInfo & info, Scope & scope) {
		std::stringstream ss;
		if(ret.expression) {
			auto code = compile::expression(*ret.expression, info, scope);
			ss << code.code;
		}
		else {
			ss << inst::null;
		}

		// For returns from iife
		if(const auto returns_to = scope.get_return()) {
			ss << inst::jump(*returns_to);
		}
		else {
			ss << inst::reTurn;
		}
		return {ss.str(), 0};
	}
}