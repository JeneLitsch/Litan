#include "compile.hxx"
namespace ltn::c {
	sst::stmt_ptr analyze_stmt(
		const ast::Throw & thr0w,
		CompilerInfo & info,
		Scope & scope) {
		
		InstructionBuffer buf;
		if(thr0w.expression) {
			buf << analyze_expression(*thr0w.expression, info, scope).code;
		}
		else {
			buf << inst::null();
		}
		buf << inst::thr0w();
		return { buf, 0 };
	}
}