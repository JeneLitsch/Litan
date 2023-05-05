#include "analyze.hxx"
#include <string_view>
namespace ltn::c {
	namespace {
		template<typename Node>
		sst::expr_ptr analyze_collection(const auto & ast_collection, Scope & scope) {
			
			std::vector<sst::expr_ptr> elements;
			for(const auto & elem : ast_collection.elements) {
				auto result = analyze_expression(*elem, scope);
				elements.push_back(std::move(result));
			}
			auto sst_collection = std::make_unique<Node>();
			sst_collection->elements = std::move(elements);
			return sst_collection;
		}
	}



	sst::expr_ptr analyze_expr(const ast::Array & array, Scope & scope) {
		return analyze_collection<sst::Array>(array, scope);
	}



	sst::expr_ptr analyze_expr(const ast::Tuple & tuple, Scope & scope) {
		return analyze_collection<sst::Tuple>(tuple, scope);
	}
}