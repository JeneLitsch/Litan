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

	

	std::unique_ptr<ast::Expression> factor(lex::Lexer & lexer) {
		auto l = unary(lexer);
		if(lexer.match(TT::STAR)) {
			auto r = factor(lexer);
			return bin(lexer, OP::MLT, l, r);
		}
		if(lexer.match(TT::SLASH)) {
			auto r = factor(lexer);
			return bin(lexer, OP::DIV, l, r);
		}
		if(lexer.match(TT::PERCENT)) {
			auto r = factor(lexer);
			return bin(lexer, OP::MOD, l, r);
		}
		return l;
	}

	std::unique_ptr<ast::Expression> term(lex::Lexer & lexer) {
		auto l = factor(lexer);
		if(lexer.match(TT::PLUS)) {
			auto r = term(lexer);
			return bin(lexer, OP::ADD, l, r);
		}
		if(lexer.match(TT::MINUS)) {
			auto r = term(lexer);
			return bin(lexer, OP::SUB, l, r);
		}
		return l;
	}

	std::unique_ptr<ast::Expression> comparision(lex::Lexer & lexer) {
		auto l = term(lexer);
		if(lexer.match(TT::SMALLER)) {
			auto r = comparision(lexer);
			return bin(lexer, OP::SMALLER, l, r);
		}
		if(lexer.match(TT::SMALLER_EQUAL)) {
			auto r = comparision(lexer);
			return bin(lexer, OP::SMALLEREQUAL, l, r);
		}
		if(lexer.match(TT::BIGGER)) {
			auto r = comparision(lexer);
			return bin(lexer, OP::BIGGER, l, r);
		}
		if(lexer.match(TT::BIGGER_EQUAL)) {
			auto r = comparision(lexer);
			return bin(lexer, OP::BIGGEREQUAL, l, r);
		}
		return l;
	}

	std::unique_ptr<ast::Expression> equality(lex::Lexer & lexer) {
		auto l = comparision(lexer);
		if(lexer.match(TT::EQUAL)) {
			auto r = equality(lexer);
			return bin(lexer, OP::EQUAL, l, r);
		}
		if(lexer.match(TT::UNEQUAL)) {
			auto r = equality(lexer);
			return bin(lexer, OP::UNEQUEL, l, r);
		}
		return l;
	}

}

