#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		using OP = ltn::c::ast::Binary::Type;
	}

	std::unique_ptr<ast::Binary> bin(OP op, auto && l, auto && r) {
		return std::make_unique<ast::Binary>(op, std::move(l), std::move(r));
	}

	

	std::unique_ptr<ast::Expression> factor(lex::Lexer & lexer) {
		auto l = unary(lexer);
		if(lexer.match(TT::STAR)) {
			auto r = factor(lexer);
			return bin(OP::MLT, l, r);
		}
		if(lexer.match(TT::SLASH)) {
			auto r = factor(lexer);
			return bin(OP::DIV, l, r);
		}
		if(lexer.match(TT::PERCENT)) {
			auto r = factor(lexer);
			return bin(OP::MOD, l, r);
		}
		return l;
	}

	std::unique_ptr<ast::Expression> term(lex::Lexer & lexer) {
		auto l = factor(lexer);
		if(lexer.match(TT::PLUS)) {
			auto r = term(lexer);
			return bin(OP::ADD, l, r);
		}
		if(lexer.match(TT::MINUS)) {
			auto r = term(lexer);
			return bin(OP::SUB, l, r);
		}
		return l;
	}

	std::unique_ptr<ast::Expression> comparision(lex::Lexer & lexer) {
		auto l = term(lexer);
		if(lexer.match(TT::SMALLER)) {
			auto r = comparision(lexer);
			return bin(OP::SMALLER, l, r);
		}
		if(lexer.match(TT::SMALLER_EQUAL)) {
			auto r = comparision(lexer);
			return bin(OP::SMALLEREQUAL, l, r);
		}
		if(lexer.match(TT::BIGGER)) {
			auto r = comparision(lexer);
			return bin(OP::BIGGER, l, r);
		}
		if(lexer.match(TT::BIGGER_EQUAL)) {
			auto r = comparision(lexer);
			return bin(OP::BIGGEREQUAL, l, r);
		}
		return l;
	}

	std::unique_ptr<ast::Expression> equality(lex::Lexer & lexer) {
		auto l = comparision(lexer);
		if(lexer.match(TT::EQUAL)) {
			auto r = equality(lexer);
			return bin(OP::EQUAL, l, r);
		}
		if(lexer.match(TT::UNEQUAL)) {
			auto r = equality(lexer);
			return bin(OP::UNEQUEL, l, r);
		}
		return l;
	}

}

