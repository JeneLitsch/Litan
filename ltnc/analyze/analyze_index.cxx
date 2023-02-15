#include "analyze.hxx"
#include <string_view>
#include "stdxx/iife.hxx"

namespace ltn::c {
	// compiles index read operation
	sst::expr_ptr analyze_expr(
		const ast::Index & index,
		Context & context,
		Scope & scope) {

		auto arr = analyze_expression(index.expression, context, scope);
		auto idx = analyze_expression(index.index, context, scope);

		type::Type type = stx::iife([&] {
			if(auto integer = as<sst::Integer>(*idx)) {
				return type::deduce_index(arr->type, idx->type, integer->value);
			}
			else {
				return type::deduce_index(arr->type, idx->type);
			}
		});
		
		return std::make_unique<sst::Index>(
			std::move(arr),
			std::move(idx),
			type
		);
	}
}