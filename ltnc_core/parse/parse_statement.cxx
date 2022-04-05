#include "parse.hxx"
#include "ltnc_core/lex/lexing.hxx"
#include "ltnc_core/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}
	
	void semicolon(lex::Lexer & lexer) {
		if(!lexer.match(TT::SEMICOLON)) {
			throw CompilerError{"missing ;", lexer.location()};
		}
		while(lexer.match(TT::SEMICOLON));
	}




	template<class AstNodeType, TT tt>
	// parses variable creation -> var a ...  
	std::unique_ptr<AstNodeType> initialize_variable(lex::Lexer & lexer) {
		if(lexer.match(tt)) {
			auto name = parse::variable_name(lexer);
			auto && r = parse::assign_r(lexer);
			semicolon(lexer);
			return std::make_unique<AstNodeType>(
				name,
				std::move(r),
				lexer.location());
		}
		return nullptr;
	}

	constexpr auto new_variable = initialize_variable<ast::NewVar, TT::VAR>;

	// parses return statement -> return ...
	ast::stmt_ptr retrn(lex::Lexer & lexer) {
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


	ast::stmt_ptr thr0w(lex::Lexer & lexer) {
		if(lexer.match(TT::THROW)) {
			std::unique_ptr<ast::Expression> expr = nullptr;
			if(!lexer.match(TT::SEMICOLON)) {
				expr = parse::expression(lexer);
				semicolon(lexer);
			}
			return std::make_unique<ast::Throw>(
				std::move(expr),
				lexer.location());
		}
		else return nullptr;
	}


	ast::stmt_ptr statement(lex::Lexer & lexer) {
		while(lexer.match(TT::SEMICOLON));
		if(auto stmt = block(lexer))        return stmt;
		if(auto stmt = if_else(lexer))      return stmt;
		if(auto stmt = while_loop(lexer))   return stmt;
		if(auto stmt = for_loop(lexer))     return stmt;
		if(auto stmt = new_variable(lexer)) return stmt;
		if(auto stmt = thr0w(lexer))        return stmt;
		if(auto stmt = retrn(lexer))        return stmt;
		auto stmt =  just_an_expr(lexer);
		semicolon(lexer);
		return stmt;
	}
}