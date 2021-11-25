#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		using OP = ltn::c::ast::Binary::Type;
	}

	std::unique_ptr<ast::Binary> bin(lex::Lexer & lexer, OP op, auto && l, auto && r) {
		return std::make_unique<ast::Binary>(op, std::move(l), std::move(r), lexer.debug());
	}

	// Operators * / %
	std::unique_ptr<ast::Expression> factor(lex::Lexer & lexer) {
		auto l = unary(lexer);
		while(true) {
			if(lexer.match(TT::STAR)) {
				auto r = unary(lexer);
				l = bin(lexer, OP::MLT, l, r);
			}
			else if(lexer.match(TT::SLASH)) {
				auto r = unary(lexer);
				l = bin(lexer, OP::DIV, l, r);
			}
			else if(lexer.match(TT::PERCENT)) {
				auto r = unary(lexer);
				l = bin(lexer, OP::MOD, l, r);
			}
			else return l;
		}
	}

	// Operators + -
	std::unique_ptr<ast::Expression> term(lex::Lexer & lexer) {
		auto l = factor(lexer);
		while(true) {
			if(lexer.match(TT::PLUS)) {
				auto r = factor(lexer);
				l = bin(lexer, OP::ADD, l, r);
			}
			else if(lexer.match(TT::MINUS)) {
				auto r = factor(lexer);
				l = bin(lexer, OP::SUB, l, r);
			}
			else return l;
		}
	}

	// Operators << >>
	std::unique_ptr<ast::Expression> shift(lex::Lexer & lexer) {
		auto l = term(lexer);
		while(true) {
			if(lexer.match(TT::SHIFT_L)) {
				auto r = term(lexer);
				l = bin(lexer, OP::SHIFT_L, l, r);
			}
			else if(lexer.match(TT::SHIFT_R)) {
				auto r = term(lexer);
				l = bin(lexer, OP::SHIFT_R, l, r);
			}
			else return l;
		}
	}

	// Operators < <= => >
	std::unique_ptr<ast::Expression> comparision(lex::Lexer & lexer) {
		auto l = shift(lexer);
		while(true) {
			if(lexer.match(TT::SMALLER)) {
				auto r = shift(lexer);
				l = bin(lexer, OP::SMALLER, l, r);
			}
			else if(lexer.match(TT::SMALLER_EQUAL)) {
				auto r = shift(lexer);
				l = bin(lexer, OP::SMALLEREQUAL, l, r);
			}
			else if(lexer.match(TT::BIGGER)) {
				auto r = shift(lexer);
				l = bin(lexer, OP::BIGGER, l, r);
			}
			else if(lexer.match(TT::BIGGER_EQUAL)) {
				auto r = shift(lexer);
				l = bin(lexer, OP::BIGGEREQUAL, l, r);
			}
			else return l;
		}
	}

	// Operators == != 
	std::unique_ptr<ast::Expression> equality(lex::Lexer & lexer) {
		auto l = comparision(lexer);
		while(true) {
			if(lexer.match(TT::EQUAL)) {
				auto r = comparision(lexer);
				l = bin(lexer, OP::EQUAL, l, r);
			}
			else if(lexer.match(TT::UNEQUAL)) {
				auto r = comparision(lexer);
				l = bin(lexer, OP::UNEQUEL, l, r);
			}
			else return l;
		}
	}

}

