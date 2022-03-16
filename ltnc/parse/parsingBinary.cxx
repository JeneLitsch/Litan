#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		using OP = ltn::c::ast::SimpleBinary::Type;


		template<class ExprType>
		ast::expr_ptr binary(
			lex::Lexer & lexer,
			const auto & op_table,
			auto presedence_down) {
			
			auto l = presedence_down(lexer);
			while (auto op = match_op(lexer, op_table)) {
				auto && r = presedence_down(lexer);
				auto expr = std::make_unique<ExprType>(
					*op,
					std::move(l),
					std::move(r),
					lexer.location());
				l = std::move(expr);
			}				
			return l;
		}
	}



	// Operators * / %
	ast::expr_ptr factor(lex::Lexer & lexer) {
		constexpr std::array table {
			std::pair{TT::STAR, OP::MLT},
			std::pair{TT::SLASH, OP::DIV},
			std::pair{TT::PERCENT, OP::MOD},
		};
		return binary<ast::SimpleBinary>(lexer, table, unary);
	}

	// Operators + -
	ast::expr_ptr term(lex::Lexer & lexer) {
		constexpr std::array table {
			std::pair{TT::PLUS,          OP::ADD},
			std::pair{TT::MINUS,         OP::SUB},
		};
		return binary<ast::SimpleBinary>(lexer, table, factor);
	}

	// Operators << >>
	ast::expr_ptr shift(lex::Lexer & lexer) {
		constexpr std::array table {
			std::pair{TT::SHIFT_L,       OP::SHIFT_L},
			std::pair{TT::SHIFT_R,       OP::SHIFT_R},
		};
		return binary<ast::SimpleBinary>(lexer, table, term); 
	}

	// Operators < <= => >
	ast::expr_ptr comparision(lex::Lexer & lexer) {
		constexpr std::array table {
			std::pair{TT::SMALLER,       OP::SMALLER},
			std::pair{TT::SMALLER_EQUAL, OP::SMALLEREQUAL},
			std::pair{TT::BIGGER,        OP::BIGGER},
			std::pair{TT::BIGGER_EQUAL,  OP::BIGGEREQUAL},
		};
		return binary<ast::SimpleBinary>(lexer, table, shift);
	}


	// Operators == != 
	ast::expr_ptr equality(lex::Lexer & lexer) {
		constexpr std::array table {
			std::pair{TT::EQUAL,         OP::EQUAL},
			std::pair{TT::UNEQUAL,       OP::UNEQUEL},
			std::pair{TT::TILDEx2,       OP::APPROX},
			std::pair{TT::XMARK_TILDE,   OP::NOTPROX},
		};
		return binary<ast::SimpleBinary>(lexer, table, comparision); 
	}

	// Operator <=>
	ast::expr_ptr spaceship(lex::Lexer & lexer) {
		constexpr std::array table {
			std::pair{TT::SPACE_SHIP,    OP::SPACE_SHIP},
		};
		return binary<ast::SimpleBinary>(lexer, table, equality); 
	}

	ast::expr_ptr logical_or(lex::Lexer & lexer) {
		constexpr std::array table {
			std::pair{TT::OR, ast::Logical::Type::OR}
		};
		return binary<ast::Logical>(lexer, table, spaceship);
	}

	ast::expr_ptr logical_and(lex::Lexer & lexer) {
		constexpr std::array table {
			std::pair{TT::AND, ast::Logical::Type::AND}
		};
		return binary<ast::Logical>(lexer, table, logical_or);
	}


}

