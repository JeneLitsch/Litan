#include "analyze.hxx"
#include <string_view>
namespace ltn::c {
	namespace {
		template<typename Node, auto deduce_type>
		sst::expr_ptr analyze_collection(const auto & ast_collection, Scope & scope) {
			
			std::vector<type::Type> elem_types;
			std::vector<sst::expr_ptr> elements;
			for(const auto & elem : ast_collection.elements) {
				auto result = analyze_expression(*elem, scope);
				elem_types.push_back(result->type);
				elements.push_back(std::move(result));
			}
			auto full_type = deduce_type(elem_types);
			auto sst_collection = std::make_unique<Node>(full_type);
			sst_collection->elements = std::move(elements);
			return sst_collection;
		}
	}



	sst::expr_ptr analyze_expr(const ast::Array & array, Scope & scope) {
		return analyze_collection<sst::Array, type::deduce_array_of>(
			array,
			scope
		);
	}



	sst::expr_ptr analyze_expr(const ast::Tuple & tuple, Scope & scope) {
		return analyze_collection<sst::Tuple, type::deduce_tuple_of>(
			tuple,
			scope
		);
	}
}