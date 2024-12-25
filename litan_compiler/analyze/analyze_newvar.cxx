#include "analyze.hxx"
#include <iostream>
#include "litan_compiler/ast/bind/NewVar.hxx"
#include "litan_compiler/ast/stmt/NewVar.hxx"
#include "litan_compiler/sst/expr/Literal.hxx"
#include "litan_compiler/sst/stmt/Assign.hxx"

namespace ltn::c {
	sst::stmt_ptr analyze_stmt(const ast::stmt::NewVar & new_var, Scope & scope) {
		auto expr 
			= new_var.expr
			? analyze_expression(*new_var.expr, scope)
			: sst::expr::null();
		auto binding = analyze_binding(*new_var.binding, scope);
		return sst::stmt::assign(std::move(binding), std::move(expr));
	}
}