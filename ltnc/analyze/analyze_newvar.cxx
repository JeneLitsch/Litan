#include "analyze.hxx"
#include <iostream>
#include "ltnc/sst/expr/Literal.hxx"
#include "ltnc/sst/stmt/Assign.hxx"

namespace ltn::c {
	sst::stmt_ptr analyze_stmt(const ast::NewVar & new_var, Scope & scope) {
		auto expr 
			= new_var.expr
			? analyze_expression(*new_var.expr, scope)
			: sst::null();
		auto binding = analyze_binding(*new_var.binding, scope);
		return sst::assign(std::move(binding), std::move(expr));
	}
}