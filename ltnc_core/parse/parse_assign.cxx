#include "parse.hxx"
#include "ltnc_core/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = lex::Token::Type;
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
		};



		template<class To, class From>
		std::unique_ptr<To> static_unique_cast(std::unique_ptr<From> && from) {
			return std::unique_ptr<To>(static_cast<To*>(from.release()));
		}



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



		ast::stmt_ptr modify(lex::Lexer & lexer, ast::expr_ptr && expr,	Op op) {
			guard_assingable(*expr, lexer.location());
			auto l = static_unique_cast<ast::Assignable>(std::move(expr));
			auto r = expression(lexer);
			return std::make_unique<ast::Modify>(
				op,
				std::move(l),
				std::move(r),
				lexer.location());
		}



		ast::stmt_ptr assignment(lex::Lexer & lexer, auto && expr, auto && r) {
			guard_assingable(*expr, lexer.location());
			return std::make_unique<ast::Assign>(
				static_unique_cast<ast::Assignable>(std::move(expr)),
				std::move(r),
				lexer.location());
		}
	}



	ast::expr_ptr assign(lex::Lexer & lexer) {
		auto l = expression(lexer);


		
		return l;
	}



	// parses Statement consiting of an Expression
	ast::stmt_ptr just_an_expr(lex::Lexer & lexer) {
		auto l = expression(lexer);
		if(auto r = assign_r(lexer)) {
			return assignment(lexer, std::move(l), std::move(r));
		}
		
		if(const auto op = match_op(lexer, op_table)) {
			return modify(lexer, std::move(l), *op);
		}
		return std::make_unique<ast::StatementExpression>(
			std::move(l),
			lexer.location());
	}



	// Tries parsing assignment after and including =
	ast::expr_ptr assign_r(lex::Lexer & lexer) {
		if(lexer.match(TT::ASSIGN)) {
			return expression(lexer);
		}
		return nullptr;
	}
}