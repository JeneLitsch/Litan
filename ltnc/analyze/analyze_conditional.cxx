#include "analyze.hxx"
#include <string_view>
#include <iostream>
#include "ltnc/ast/expr/Conditional.hxx"
#include "ltnc/ast/stmt/Conditional.hxx"
#include "ltnc/sst/expr/Literal.hxx"
#include "ltnc/sst/stmt/NoOp.hxx"

namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::expr::Conditional & conditional, Scope & scope) {
		std::cout << "EXPR::CONDITIONAL: " << std::size(conditional.cases) << "\n";
		return sst::expr::null();
	}



	sst::stmt_ptr analyze_stmt(const ast::stmt::Conditional & conditional, Scope & scope) {
		std::cout << "STMT::CONDITIONAL: " << std::size(conditional.cases) << "\n";
		return sst::stmt::no_op();
	}
}