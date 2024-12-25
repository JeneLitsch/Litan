#include "analyze.hxx"
#include <string_view>
#include <iostream>
#include "litan_compiler/ast/expr/Conditional.hxx"
#include "litan_compiler/ast/stmt/Conditional.hxx"
#include "litan_compiler/sst/expr/Conditional.hxx"
#include "litan_compiler/sst/stmt/Conditional.hxx"
#include "litan_compiler/sst/expr/Literal.hxx"
#include "litan_compiler/sst/stmt/NoOp.hxx"

#include "litan_compiler/scoping/CaseScope.hxx"
#include "litan_compiler/scoping/BlockScope.hxx"

namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::expr::Conditional & ast, Scope & scope) {
		auto sst = sst::expr::conditional();
		for(auto & [c, b] : ast.cases) {
			BlockScope body_scope {&scope};
			sst->add_case(analyze_expression(*c, scope), analyze_expression(*b, body_scope));
		}
		if(ast.else_branch) {
			BlockScope body_scope {&scope};
			sst->set_else(analyze_expression(*ast.else_branch, body_scope));
		}
		else {
			sst->set_else(sst::expr::null());
		}
		return sst;
	}



	sst::stmt_ptr analyze_stmt(const ast::stmt::Conditional & ast, Scope & scope) {
		auto sst = sst::stmt::conditional();
		for(auto & [c, b] : ast.cases) {
			BlockScope body_scope {&scope};
			sst->add_case(analyze_expression(*c, scope), analyze_statement(*b, body_scope));
		}
		if(ast.else_branch) {
			BlockScope body_scope {&scope};
			sst->set_else(analyze_statement(*ast.else_branch, body_scope));
		}
		else {
			sst->set_else(sst::stmt::no_op());
		}
		return sst;
	}
}