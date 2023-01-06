#include "analyze.hxx"
#include <string_view>
namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::Array & array, Context & context, Scope & scope) {
		type::Array type;
		std::vector<sst::expr_ptr> elements;
		for(const auto & elem : array.elements) {
			auto result = analyze_expression(*elem, context, scope);
			type = type::deduce_array_append(type, result->type);
			elements.push_back(std::move(result));
		}
		auto arr = std::make_unique<sst::Array>(type);
		arr->elements = std::move(elements);
		return arr;
	}
}