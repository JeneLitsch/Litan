#include "analyze.hxx"
namespace ltn::c {
	sst::stmt_ptr analyze_stmt(
		const ast::Throw & thr0w,
		Context & context,
		Scope & scope) {
		
		if(thr0w.expr) {
			auto expr = analyze_expression(*thr0w.expr, context, scope);
			return std::make_unique<sst::Throw>(
				std::move(expr)
			);
		}
		else {
			return std::make_unique<sst::Throw>(
				std::make_unique<sst::Null>(type::Null{})
			);
		}
	}
}