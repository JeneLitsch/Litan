#include "analyze.hxx"
#include <string_view>
#include "litan_compiler/ast/expr/Array.hxx"
#include "litan_compiler/ast/expr/Tuple.hxx"
#include "litan_compiler/sst/expr/Array.hxx"
#include "litan_compiler/sst/expr/Tuple.hxx"

namespace ltn::c {
	namespace {
		sst::expr_ptr analyze_collection(const auto & ast, const auto & make_sst, Scope & scope) {
			auto sst = make_sst();
			for(const auto & elem : ast.elements) {
				sst->push_back(analyze_expression(*elem, scope));
			}
			return sst;
		}
	}



	sst::expr_ptr analyze_expr(const ast::expr::Array & array, Scope & scope) {
		return analyze_collection(array, sst::expr::array, scope);
	}



	sst::expr_ptr analyze_expr(const ast::expr::Tuple & tuple, Scope & scope) {
		return analyze_collection(tuple, sst::expr::tuple, scope);
	}
}