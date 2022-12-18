#include "analyze.hxx"
namespace ltn::c {
	sst::stmt_ptr analyze_stmt(
		const ast::Throw & thr0w,
		Context & context,
		Scope & scope) {
		
		if(thr0w.expression) {
			auto expr = analyze_expression(*thr0w.expression, context, scope);
			return std::make_unique<sst::Throw>(0, false, std::move(expr));
		}
		else {
			return std::make_unique<sst::Throw>(0, false, std::make_unique<sst::Null>(type::Null{}));
		}
	}
}