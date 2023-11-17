#include "analyze.hxx"
#include <string_view>
#include "ltnc/ast/expr/Iife.hxx"
#include "ltnc/sst/expr/Iife.hxx"

namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::expr::Iife & iife, Scope & outer_scope) {

		const auto return_label = make_jump_id("IIFE");
		MinorScope inner_scope{&outer_scope};
		inner_scope.set_return(return_label);
		auto body = analyze_statement(*iife.stmt, inner_scope);

		return sst::expr::iife(std::move(return_label), std::move(body));
	}
}