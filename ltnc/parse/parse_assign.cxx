#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include "stdxx/memory.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;
		using Op = ast::Modify::Type;



		constexpr auto op_table = std::array{
			std::pair{TT::ASSIGN_ADD,     Op::ADD},
			std::pair{TT::ASSIGN_SUB,     Op::SUB},
			std::pair{TT::ASSIGN_MLT,     Op::MLT},
			std::pair{TT::ASSIGN_DIV,     Op::DIV},
			std::pair{TT::ASSIGN_MOD,     Op::MOD},
			std::pair{TT::ASSIGN_SHIFT_L, Op::SHIFT_L},
			std::pair{TT::ASSIGN_POW,     Op::POW},
			std::pair{TT::ASSIGN_SHIFT_R, Op::SHIFT_R},
			std::pair{TT::ASSIGN_BIT_XOR, Op::BITXOR},
			std::pair{TT::ASSIGN_BIT_AND,  Op::BITAND},
			std::pair{TT::ASSIGN_BIT_OR,   Op::BITOR},
		};



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



		ast::stmt_ptr modify(Tokens & tokens, ast::expr_ptr && expr,	Op op) {
			guard_assingable(*expr, location(tokens));
			auto l = stx::static_unique_cast<ast::Assignable>(std::move(expr));
			auto r = parse_expression(tokens);
			return std::make_unique<ast::Modify>(
				op,
				std::move(l),
				std::move(r),
				location(tokens));
		}



		ast::stmt_ptr assignment(Tokens & tokens, auto && expr, auto && r) {
			guard_assingable(*expr, location(tokens));
			return std::make_unique<ast::Assign>(
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
		
		if(const auto op = match_op(tokens, op_table)) {
			return modify(tokens, std::move(l), *op);
		}
		return std::make_unique<ast::StatementExpression>(
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