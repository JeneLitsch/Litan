#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include "stdxx/memory.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;

		bool is_assingable(auto & from) {
			return dynamic_cast<const ast::Assignable * const>(&from);
		}



		void guard_assingable(auto & expr, auto location) {
			if(!is_assingable(expr)) {
				throw CompilerError{
					"Left side of an assignment must be an assignable expression",
					location};
			}
		}



		ast::stmt_ptr assignment(Tokens & tokens, auto && expr, auto && r) {
			guard_assingable(*expr, location(tokens));
			return stx::make_unique<ast::Assign>(
				stx::static_unique_cast<ast::Assignable>(std::move(expr)),
				std::move(r),
				location(tokens));
		}
	}



	ast::expr_ptr assign(Tokens & tokens) {
		auto l = parse_expression(tokens);
		return l;
	}



	// parses Statement consiting of an Expression
	ast::stmt_ptr parse_just_an_expr(Tokens & tokens) {
		auto l = parse_expression(tokens);
		if(auto r = parse_assign_r(tokens)) {
			return assignment(tokens, std::move(l), std::move(r));
		}
		return stx::make_unique<ast::StatementExpression>(
			std::move(l),
			location(tokens));
	}



	// Tries parsing assignment after and including =
	ast::expr_ptr parse_assign_r(Tokens & tokens) {
		if(match(TT::ASSIGN, tokens)) {
			return parse_expression(tokens);
		}
		return nullptr;
	}
}