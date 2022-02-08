#include "parsing.hxx"
#include "ltnc/lex/lexing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	// Maches ; or throws
	void semicolon(lex::Lexer & lexer) {
		if(!lexer.match(TT::SEMICOLON)) {
			throw CompilerError{"missing ;", lexer.location()};
		}
		while(lexer.match(TT::SEMICOLON));
	}

	// Enforces ; after statement
	std::unique_ptr<ast::Statement> semicolon(lex::Lexer & lexer, auto fx) {
		auto stmt = fx(lexer);
		if(!stmt) return nullptr;
		semicolon(lexer);
		return stmt;
	}

	// parses Statement consiting of an Expression
	auto expr(lex::Lexer & lexer) {
		return std::make_unique<ast::StatementExpression>(assign(lexer), lexer.location());
	}

	template<class AstNodeType, TT tt>
	// parses variable creation -> var a ...  
	std::unique_ptr<AstNodeType> initVar(lex::Lexer & lexer) {
		if(lexer.match(tt)) {
			auto name = parse::variableName(lexer);
			auto && r = parse::assignR(lexer);
			return std::make_unique<AstNodeType>(
				name,
				std::move(r),
				lexer.location());
		}
		return nullptr;
	}

	constexpr auto newVar = initVar<ast::NewVar, TT::VAR>;
	constexpr auto newConst = initVar<ast::NewConst, TT::CONST>;

	// parses return statement -> return ...
	std::unique_ptr<ast::Statement> retrn(lex::Lexer & lexer) {
		if(lexer.match(TT::RETURN)) {
			if(lexer.match(TT::SEMICOLON)) {
				return std::make_unique<ast::Return>(nullptr, lexer.location());
			}
			auto expr = expression(lexer);
			semicolon(lexer);
			return std::make_unique<ast::Return>(std::move(expr), lexer.location());
		}
		return nullptr;
	}


	std::unique_ptr<ast::Statement> statement(lex::Lexer & lexer) {
		while(lexer.match(TT::SEMICOLON));
		if(auto stmt = block(lexer)) return stmt;
		if(auto stmt = ifElse(lexer)) return stmt;
		if(auto stmt = whileLoop(lexer)) return stmt;
		if(auto stmt = forLoop(lexer)) return stmt;
		if(auto stmt = semicolon(lexer, newVar)) return stmt;
		if(auto stmt = semicolon(lexer, newConst)) return stmt;
		if(auto stmt = retrn(lexer)) return stmt;
		return semicolon(lexer, expr);
	}
}