#include "analyze.hxx"
#include <iostream>
#include "ltnc/sst/expr/Literal.hxx"

namespace ltn::c {
	namespace {
		sst::expr_ptr analyze_new_variable_right(const ast::NewVar & new_var, Scope & scope) {
			
			if(new_var.expr) {
				return  analyze_expression(*new_var.expr, scope);
			}
			else {
				return std::make_unique<sst::Null>();
			}
		}
	}



	sst::stmt_ptr analyze_stmt(const ast::NewVar & new_var, Scope & scope) {

		auto expr = analyze_new_variable_right(new_var, scope);
		auto binding = analyze_binding(*new_var.binding, scope);
		return std::make_unique<sst::Assign>(std::move(binding), std::move(expr));
	}
}