#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		using OP = ltn::c::ast::Binary::Type;

		std::unique_ptr<ast::Binary> bin(
			lex::Lexer & lexer, OP op, auto && l, auto && r) {
		
			return std::make_unique<ast::Binary>(
				op, std::move(l), std::move(r), lexer.debug());
		}

		std::pair<bool, std::unique_ptr<ast::Expression>> fromTable(
			lex::Lexer & lexer,
			const auto & opTable,
			auto presedenceDown,
			auto && l) {
			
			for(const auto & [tt, op] : opTable) {
				if(lexer.match(tt)) {
					auto && r = presedenceDown(lexer);
					return {false, bin(lexer, op, l, r)};
				}
			}
			return {true, std::move(l)};
		}

		std::unique_ptr<ast::Expression> binary(
			lex::Lexer & lexer, const auto & opTable, auto presedenceDown) {
			while(true) {
				auto l = presedenceDown(lexer);
				while (true) {
					auto [last, expr] = fromTable(lexer, opTable, presedenceDown, l);
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
		return binary(lexer, table, unary);
	}

	// Operators + -
	std::unique_ptr<ast::Expression> term(lex::Lexer & lexer) {
		constexpr std::array table {
			std::pair{TT::PLUS, OP::ADD},
			std::pair{TT::MINUS, OP::SUB},
		};
		return binary(lexer, table, factor);
	}

	// Operators << >>
	std::unique_ptr<ast::Expression> shift(lex::Lexer & lexer) {
		constexpr std::array table {
			std::pair{TT::SHIFT_L, OP::SHIFT_L},
			std::pair{TT::SHIFT_R, OP::SHIFT_R},
		};
		return binary(lexer, table, term); 
	}

	// Operators < <= => >
	std::unique_ptr<ast::Expression> comparision(lex::Lexer & lexer) {
		constexpr std::array table {
			std::pair{TT::SMALLER, OP::SMALLER},
			std::pair{TT::SMALLER_EQUAL, OP::SMALLEREQUAL},
			std::pair{TT::BIGGER, OP::BIGGER},
			std::pair{TT::BIGGER_EQUAL, OP::BIGGEREQUAL},
		};
		return binary(lexer, table, shift);
	}

	// Operators == != 
	std::unique_ptr<ast::Expression> equality(lex::Lexer & lexer) {
		constexpr std::array table {
			std::pair{TT::EQUAL, OP::EQUAL},
			std::pair{TT::UNEQUAL, OP::UNEQUEL},
		};
		return binary(lexer, table, comparision); 
	}

}

