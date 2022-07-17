#include "parse.hxx"
#include "ltnc/lex/lexing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}
	
	void semicolon(LexBuffer & lexer) {
		if(!lexer.match(TT::SEMICOLON)) {
			throw CompilerError{"missing ;", lexer.location()};
		}
		while(lexer.match(TT::SEMICOLON));
	}




	template<class AstNodeType, TT tt>
	// parses variable creation -> var a ...  
	std::unique_ptr<AstNodeType> parse_initialize_variable(LexBuffer & lexer) {
		if(lexer.match(tt)) {
			auto name = parse_variable_name(lexer);
			auto && r = parse_assign_r(lexer);
			semicolon(lexer);
			return std::make_unique<AstNodeType>(
				name,
				std::move(r),
				lexer.location());
		}
		return nullptr;
	}

	constexpr auto parse_new_variable = parse_initialize_variable<ast::NewVar, TT::VAR>;

	// parses return statement -> return ...
	ast::stmt_ptr parse_return(LexBuffer & lexer) {
		if(lexer.match(TT::RETURN)) {
			if(lexer.match(TT::SEMICOLON)) {
				return std::make_unique<ast::Return>(nullptr, lexer.location());
			}
			auto expr = parse_expression(lexer);
			semicolon(lexer);
			return std::make_unique<ast::Return>(std::move(expr), lexer.location());
		}
		return nullptr;
	}


	ast::stmt_ptr parse_throw(LexBuffer & lexer) {
		if(lexer.match(TT::THROW)) {
			std::unique_ptr<ast::Expression> expr = nullptr;
			if(!lexer.match(TT::SEMICOLON)) {
				expr = parse_expression(lexer);
				semicolon(lexer);
			}
			return std::make_unique<ast::Throw>(
				std::move(expr),
				lexer.location());
		}
		else return nullptr;
	}


	ast::stmt_ptr parse_statement(LexBuffer & lexer) {
		while(lexer.match(TT::SEMICOLON));
		if(auto stmt = parse_block(lexer))        return stmt;
		if(auto stmt = parse_if_else(lexer))      return stmt;
		if(auto stmt = parse_while_loop(lexer))   return stmt;
		if(auto stmt = parse_for_loop(lexer))     return stmt;
		if(auto stmt = parse_new_variable(lexer)) return stmt;
		if(auto stmt = parse_throw(lexer))        return stmt;
		if(auto stmt = parse_return(lexer))        return stmt;
		if(auto stmt = parse_stmt_switch(lexer))  return stmt;
		auto stmt =  parse_just_an_expr(lexer);
		semicolon(lexer);
		return stmt;
	}
}