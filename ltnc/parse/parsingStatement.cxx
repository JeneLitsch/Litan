#include "parsing.hxx"
#include "ltnc/lex/lexing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	std::unique_ptr<ast::Statement> semicolon(lex::Lexer & lexer, auto fx) {
		auto stmt = fx(lexer);
		if(!stmt) return nullptr;
		if(lexer.match(TT::SEMICOLON)) {
			return stmt;
		}
		throw CompilerError{"missing semicolon", lexer.inLine()};
	}

	auto expr(lex::Lexer & lexer) {
		return std::make_unique<ast::StatementExpression>(assign(lexer), lexer.debug());
	}

	std::unique_ptr<ast::NewVar> newVar(lex::Lexer & lexer) {
		if(lexer.match(TT::VAR)) {
			auto name = parse::variableName(lexer);
			if(auto && r = parse::assignR(lexer)) {
				auto && l = std::make_unique<ast::Var>(name, lexer.debug());
				auto && assign = std::make_unique<ast::Assign>(std::move(l), std::move(r), lexer.debug()); 
				return std::make_unique<ast::NewVar>(name, std::move(assign), lexer.debug());
			} 
			return std::make_unique<ast::NewVar>(name, nullptr, lexer.debug());
		}
		return nullptr;
	}

	std::unique_ptr<ast::Return> retrn(lex::Lexer & lexer) {
		if(lexer.match(TT::RETURN)) {
			auto expr = expression(lexer);
			return std::make_unique<ast::Return>(std::move(expr), lexer.debug());
		}
		return nullptr;
	}

	void extraSemicolon(lex::Lexer & lexer) {
		while(lexer.match(TT::SEMICOLON)) {
			throw CompilerError("Extra ;", lexer.inLine());
		}
	}

	std::unique_ptr<ast::Statement> statement(lex::Lexer & lexer) {
		extraSemicolon(lexer);
		if(auto stmt = block(lexer)) return stmt;
		if(auto stmt = ifElse(lexer)) return stmt;
		if(auto stmt = whileLoop(lexer)) return stmt;
		if(auto stmt = semicolon(lexer, newVar)) return stmt;
		if(auto stmt = semicolon(lexer, retrn)) return stmt;
		return semicolon(lexer, expr);
	}
}