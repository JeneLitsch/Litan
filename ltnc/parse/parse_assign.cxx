#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include "stdxx/memory.hxx"
#include "ltnc/ast/stmt/Assign.hxx"
#include "ltnc/ast/stmt/StatementExpression.hxx"

namespace ltn::c {
	ast::stmt_ptr parse_just_an_expr(Tokens & tokens) {
		auto l = parse_expression(tokens);
		if(auto r = parse_assign_r(tokens)) {
			return ast::stmt::assign(std::move(l), std::move(r), location(tokens));
		}
		return ast::stmt::just_an_expr(std::move(l), location(tokens));
	}



	ast::expr_ptr parse_assign_r(Tokens & tokens) {
		using TT = Token::Type;
		if(match(TT::ASSIGN, tokens)) {
			return parse_expression(tokens);
		}
		return nullptr;
	}
}