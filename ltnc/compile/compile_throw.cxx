#include "compile.hxx"
namespace ltn::c {
	StmtResult compile_thr0w(const ast::Throw & thr0w, CompilerInfo & info, Scope & scope) {
		InstructionBuffer buf;
		if(thr0w.expression) {
			buf << compile_expression(*thr0w.expression, info, scope).code;
		}
		else {
			buf << ltn::inst::Null{};
		}
		buf << ltn::inst::Throw{};
		return { buf, 0 };
	}
}