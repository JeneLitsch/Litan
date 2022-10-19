#include "compile.hxx"
#include "conversion.hxx"
#include <iostream>

namespace ltn::c {
	// compiles -> return...;
	StmtCode compile_reTurn(const ast::Return & ret, CompilerInfo & info, Scope & scope) {
		InstructionBuffer buf;
		if(ret.expression) {
			auto code = compile_expression(*ret.expression, info, scope);
			buf << code.code;
			buf << conversion_on_return(code.deduced_type, scope.get_return_type(), ret.location);
		}
		else {
			buf << ltn::inst::Null{};
			buf << conversion_on_return(type::Null{}, scope.get_return_type(), ret.location);
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