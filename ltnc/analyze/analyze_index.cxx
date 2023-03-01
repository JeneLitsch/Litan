#include "analyze.hxx"
#include <string_view>
#include "stdxx/iife.hxx"

namespace ltn::c {
	namespace {
		std::optional<std::int64_t> int_constant(const sst::Integer & expr) {
			return expr.value;
		} 

		std::optional<std::int64_t> int_constant(const auto &) {
			return std::nullopt;
		}
	}



	sst::expr_ptr analyze_expr(
		const ast::Index & index,
		Context & context,
		Scope & scope) {

		auto arr = analyze_expression(*index.expr, context, scope);
		auto idx = analyze_expression(*index.index, context, scope);
		const auto constant = sst::visit_expression(*idx, [] (const auto & e) {
			return int_constant(e);
		});
		auto type = type::deduce_index(arr->type, idx->type, constant);

		return std::make_unique<sst::Index>(
			std::move(arr),
			std::move(idx),
			type
		);
	}
}