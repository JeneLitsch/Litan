#include "compile.hxx"
namespace ltn::c {
	StmtResult compile_thr0w(const ast::Throw & thr0w, CompilerInfo & info, Scope & scope) {
		InstructionBuffer buf;
		if(thr0w.expression) {
			buf << compile_expression(*thr0w.expression, info, scope).code;
		}
		else {
			buf << inst::null();
		}
		buf << inst::thr0w();
		return { buf, 0 };
	}
}