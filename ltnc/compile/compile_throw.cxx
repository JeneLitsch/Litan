#include "compile.hxx"
namespace ltn::c::compile {
	StmtCode thr0w(const ast::Throw & thr0w, CompilerInfo & info, Scope & scope) {
		std::ostringstream ss;
		if(thr0w.expression) {
			ss << compile::expression(*thr0w.expression, info, scope).code;
		}
		else {
			ss << inst::null;
		}
		ss << inst::thr0w;
		return {ss.str(), 0};
	}
}