#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		using OP = ltn::c::ast::SimpleBinary::Type;

		template<class ExprType>
		std::pair<bool, std::unique_ptr<ast::Expression>> from_table(
			lex::Lexer & lexer,
			const auto & opTable,
			auto presedence_down,
			auto && l) {
			
			for(const auto & [tt, op] : opTable) {
				if(lexer.match(tt)) {
					auto && r = presedence_down(lexer);
					auto bin = std::make_unique<ExprType>(
						op, std::move(l), std::move(r), lexer.location());
					return {false, std::move(bin)}; 
				}
			}
			return {true, std::move(l)};
		}

		template<class ResultType>
		std::unique_ptr<ast::Expression> binary(
			lex::Lexer & lexer, const auto & opTable, auto presedence_down) {
			while(true) {
				auto l = presedence_down(lexer);
				while (true) {
					auto [last, expr] = from_table<ResultType>(
						lexer,
						opTable,
						presedence_down,
						l);
					l = std::move(expr);
					if(last) return l;
				}				
			}
		}
	}



	// Operators * / %
	std::unique_ptr<ast::Expression> factor(lex::Lexer & lexer) {
		constexpr std::array table {
			std::pair{TT::STAR, OP::MLT},
			std::pair{TT::SLASH, OP::DIV},
			std::pair{TT::PERCENT, OP::MOD},
		};
		return binary<ast::SimpleBinary>(lexer, table, unary);
	}

	// Operators + -
	std::unique_ptr<ast::Expression> term(lex::Lexer & lexer) {
		constexpr std::array table {
			std::pair{TT::PLUS, OP::ADD},
			std::pair{TT::MINUS, OP::SUB},
		};
		return binary<ast::SimpleBinary>(lexer, table, factor);
	}

	// Operators << >>
	std::unique_ptr<ast::Expression> shift(lex::Lexer & lexer) {
		constexpr std::array table {
			std::pair{TT::SHIFT_L, OP::SHIFT_L},
			std::pair{TT::SHIFT_R, OP::SHIFT_R},
		};
		return binary<ast::SimpleBinary>(lexer, table, term); 
	}

	// Operators < <= => >
	std::unique_ptr<ast::Expression> comparision(lex::Lexer & lexer) {
		constexpr std::array table {
			std::pair{TT::SMALLER, OP::SMALLER},
			std::pair{TT::SMALLER_EQUAL, OP::SMALLEREQUAL},
			std::pair{TT::BIGGER, OP::BIGGER},
			std::pair{TT::BIGGER_EQUAL, OP::BIGGEREQUAL},
		};
		return binary<ast::SimpleBinary>(lexer, table, shift);
	}


	// Operators == != 
	std::unique_ptr<ast::Expression> equality(lex::Lexer & lexer) {
		constexpr std::array table {
			std::pair{TT::EQUAL, OP::EQUAL},
			std::pair{TT::UNEQUAL, OP::UNEQUEL},
			std::pair{TT::TILDEx2, OP::APPROX},
			std::pair{TT::XMARK_TILDE, OP::NOTPROX},
		};
		return binary<ast::SimpleBinary>(lexer, table, comparision); 
	}

	// Operator <=>
	std::unique_ptr<ast::Expression> spaceship(lex::Lexer & lexer) {
		constexpr std::array table {
			std::pair{TT::SPACE_SHIP, OP::SPACE_SHIP},
		};
		return binary<ast::SimpleBinary>(lexer, table, equality); 
	}

	std::unique_ptr<ast::Expression> logical_or(lex::Lexer & lexer) {
		constexpr std::array table {
			std::pair{TT::OR, ast::Logical::Type::OR}
		};
		return binary<ast::Logical>(lexer, table, spaceship);
	}

	std::unique_ptr<ast::Expression> logical_and(lex::Lexer & lexer) {
		constexpr std::array table {
			std::pair{TT::AND, ast::Logical::Type::AND}
		};
		return binary<ast::Logical>(lexer, table, logical_or);
	}


}

