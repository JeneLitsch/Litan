#include "analyze.hxx"
namespace ltn::c {
	sst::stmt_ptr analyze_stmt(
		const ast::Throw & thr0w,
		CompilerInfo & info,
		Scope & scope) {
		
		if(thr0w.expression) {
			auto expr = analyze_expression(*thr0w.expression, info, scope);
			return std::make_unique<sst::Throw>(0, false, std::move(expr));
		}
		else {
			return std::make_unique<sst::Throw>(0, false, std::make_unique<sst::Null>(type::Null{}));
		}
	}
}