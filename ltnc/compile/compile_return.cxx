#include "compile.hxx"
namespace ltn::c::compile {
	// compiles -> return...;
	StmtCode reTurn(const ast::Return & ret, CompilerInfo & info, Scope & scope) {
		InstructionBuffer buf;
		if(ret.expression) {
			auto code = compile::expression(*ret.expression, info, scope);
			buf << code.code;
		}
		else {
			buf << ltn::inst::Null{};
		}

		// For returns from iife
		if(const auto returns_to = scope.get_return()) {
			buf << ltn::inst::Jump{*returns_to};
		}
		else {
			buf << ltn::inst::Return{};
		}
		return { buf, 0 };
	}
}