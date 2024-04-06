#include "analyze.hxx"
#include <string_view>
#include <iostream>
#include "ltnc/ast/expr/Conditional.hxx"
#include "ltnc/ast/stmt/Conditional.hxx"
#include "ltnc/sst/expr/Conditional.hxx"
#include "ltnc/sst/stmt/Conditional.hxx"
#include "ltnc/sst/expr/Literal.hxx"
#include "ltnc/sst/stmt/NoOp.hxx"

namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::expr::Conditional & ast, Scope & scope) {
		auto sst = sst::expr::conditional();
		for(auto & [c, b] : ast.cases) {
			sst->add_case(analyze_expression(*c, scope), analyze_expression(*b, scope));
		}
		if(ast.else_branch) {
			sst->set_else(analyze_expression(*ast.else_branch, scope));
		}
		return sst;
	}



	sst::stmt_ptr analyze_stmt(const ast::stmt::Conditional & ast, Scope & scope) {
		auto sst = sst::stmt::conditional();
		for(auto & [c, b] : ast.cases) {
			sst->add_case(analyze_expression(*c, scope), analyze_statement(*b, scope));
		}
		if(ast.else_branch) {
			sst->set_else(analyze_statement(*ast.else_branch, scope));
		}
		return sst;
	}
}