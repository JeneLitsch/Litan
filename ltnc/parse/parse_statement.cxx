#include "parse.hxx"
#include "ltnc/lex/lexing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;
	}
	
	void semicolon(Tokens & tokens) {
		if(!match(TT::SEMICOLON, tokens)) {
			throw CompilerError{"missing ;", location(tokens)};
		}
		while(match(TT::SEMICOLON, tokens));
	}



	std::unique_ptr<ast::NewVar> parse_new_variable(Tokens & tokens) {
		if(match(TT::VAR, tokens)) {
			auto name = parse_variable_name(tokens);
			auto type = parse_var_type_auto(tokens);
			auto && r = parse_assign_r(tokens);
			semicolon(tokens);
			return std::make_unique<ast::NewVar>(
				name,
				std::move(r),
				location(tokens),
				type
			);
		}
		return nullptr;
	}



	// parses return statement -> return ...
	ast::stmt_ptr parse_return(Tokens & tokens) {
		if(match(TT::RETURN, tokens)) {
			if(match(TT::SEMICOLON, tokens)) {
				return std::make_unique<ast::Return>(nullptr, location(tokens));
			}
			auto expr = parse_expression(tokens);
			semicolon(tokens);
			return std::make_unique<ast::Return>(std::move(expr), location(tokens));
		}
		return nullptr;
	}



	ast::stmt_ptr parse_throw(Tokens & tokens) {
		if(match(TT::THROW, tokens)) {
			std::unique_ptr<ast::Expression> expr = nullptr;
			if(!match(TT::SEMICOLON, tokens)) {
				expr = parse_expression(tokens);
				semicolon(tokens);
			}
			return std::make_unique<ast::Throw>(
				std::move(expr),
				location(tokens));
		}
		else return nullptr;
	}



	ast::stmt_ptr parse_statement(Tokens & tokens) {
		while(match(TT::SEMICOLON, tokens));
		if(auto stmt = parse_block(tokens))        return stmt;
		if(auto stmt = parse_if_else(tokens))      return stmt;
		if(auto stmt = parse_while_loop(tokens))   return stmt;
		if(auto stmt = parse_for_loop(tokens))     return stmt;
		if(auto stmt = parse_new_variable(tokens)) return stmt;
		if(auto stmt = parse_throw(tokens))        return stmt;
		if(auto stmt = parse_return(tokens))        return stmt;
		if(auto stmt = parse_stmt_switch(tokens))  return stmt;
		auto stmt =  parse_just_an_expr(tokens);
		semicolon(tokens);
		return stmt;
	}
}