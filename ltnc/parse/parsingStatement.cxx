#include "parsing.hxx"
#include "ltnc/lex/lexing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	void semicolon(lex::Lexer & lexer) {
		if(!lexer.match(TT::SEMICOLON)) {
			throw CompilerError{"missing semicolon", lexer.inLine()};
		}
	}

	std::unique_ptr<ast::Statement> semicolon(lex::Lexer & lexer, auto fx) {
		auto stmt = fx(lexer);
		if(!stmt) return nullptr;
		semicolon(lexer);
		return stmt;
	}

	auto expr(lex::Lexer & lexer) {
		return std::make_unique<ast::StatementExpression>(assign(lexer), lexer.debug());
	}

	std::unique_ptr<ast::NewVar> newVar(lex::Lexer & lexer) {
		if(lexer.match(TT::VAR)) {
			auto name = parse::variableName(lexer);
			if(auto && r = parse::assignR(lexer)) {
				return std::make_unique<ast::NewVar>(name, std::move(r), lexer.debug());
			} 
			return std::make_unique<ast::NewVar>(name, nullptr, lexer.debug());
		}
		return nullptr;
	}

	std::unique_ptr<ast::Statement> retrn(lex::Lexer & lexer) {
		if(lexer.match(TT::RETURN)) {
			if(lexer.match(TT::SEMICOLON)) {
				return std::make_unique<ast::Return>(nullptr, lexer.debug());
			}
			auto expr = expression(lexer);
			semicolon(lexer);
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
		if(auto stmt = retrn(lexer)) return stmt;
		return semicolon(lexer, expr);
	}
}