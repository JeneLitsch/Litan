#include "parsing.hxx"
#include "ltnc/lex/lexing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		using MC = ast::NewVar::MemoryClass;
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
		return std::make_unique<ast::StatementExpression>(assign(lexer));
	}

	std::unique_ptr<ast::NewVar> newVar(lex::Lexer & lexer) {
		const auto make = [&] (MC mc) {
			auto type = parse::type(lexer);
			auto name = parse::variableName(lexer);
			if(auto && r = parse::assignR(lexer)) {
				auto && l = std::make_unique<ast::Var>(name);
				auto && assign = std::make_unique<ast::Assign>(std::move(l), std::move(r)); 
				return std::make_unique<ast::NewVar>(mc, std::move(type), name, std::move(assign));
			} 
			return std::make_unique<ast::NewVar>(mc, std::move(type), name, nullptr);
		};
		if(lexer.match(TT::VAR)) return make(MC::VAR);
		if(lexer.match(TT::REF)) return make(MC::REF);
		return nullptr;
	}

	std::unique_ptr<ast::Return> retrn(lex::Lexer & lexer) {
		if(lexer.match(TT::RETURN)) {
			auto expr = expression(lexer);
			return std::make_unique<ast::Return>(std::move(expr));
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