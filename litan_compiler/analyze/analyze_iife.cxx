#include "analyze.hxx"
#include <string_view>

#include "litan_compiler/ast/expr/Iife.hxx"
#include "litan_compiler/sst/expr/Iife.hxx"
#include "litan_compiler/scoping/IifeScope.hxx"

namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::expr::Iife & iife, Scope & outer_scope) {

		const auto return_label = make_jump_id("IIFE");
		IifeScope inner_scope{&outer_scope};
		inner_scope.set_return(return_label);
		auto body = analyze_statement(*iife.stmt, inner_scope);

		return sst::expr::iife(std::move(return_label), std::move(body));
	}
}