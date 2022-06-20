#include "compile.hxx"
namespace ltn::c::compile {
	StmtCode thr0w(const ast::Throw & thr0w, CompilerInfo & info, Scope & scope) {
		InstructionBuffer buf;
		if(thr0w.expression) {
			buf << compile::expression(*thr0w.expression, info, scope).code;
		}
		else {
			buf << ltn::inst::Null{};
		}
		buf << ltn::inst::Throw{};
		return { buf, 0 };
	}
}