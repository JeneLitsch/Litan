#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/ast/stmt/Return.hxx"
#include "ltnc/ast/stmt/Yield.hxx"
#include "ltnc/ast/stmt/Throw.hxx"

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



	ast::stmt_ptr parse_return(Tokens & tokens) {
		if(match(TT::RETURN, tokens)) {
			if(match(TT::SEMICOLON, tokens)) {
				return ast::stmt::retvrn(nullptr, location(tokens));
			}
			auto expr = parse_expression(tokens);
			semicolon(tokens);
			return ast::stmt::retvrn(std::move(expr), location(tokens));
		}
		return nullptr;
	}



	ast::stmt_ptr parse_yield(Tokens & tokens) {
		if(match(TT::YIELD, tokens)) {
			if(match(TT::SEMICOLON, tokens)) {
				return ast::stmt::yield(nullptr, location(tokens));
			}
			auto expr = parse_expression(tokens);
			semicolon(tokens);
			return ast::stmt::yield(std::move(expr), location(tokens));
		}
		return nullptr;
	}



	ast::stmt_ptr parse_throw(Tokens & tokens) {
		if(match(TT::THROW, tokens)) {
			ast::expr_ptr expr = nullptr;
			if(!match(TT::SEMICOLON, tokens)) {
				expr = parse_expression(tokens);
				semicolon(tokens);
			}
			return ast::stmt::thr0w(std::move(expr), location(tokens));
		}
		else return nullptr;
	}



	ast::stmt_ptr parse_statement(Tokens & tokens) {
		while(match(TT::SEMICOLON, tokens));
		if(auto stmt = parse_block(tokens))            return stmt;
		if(auto stmt = parse_if_else(tokens))          return stmt;
		if(auto stmt = parse_while_loop(tokens))       return stmt;
		if(auto stmt = parse_for_loop(tokens))         return stmt;
		if(auto stmt = parse_newvar(tokens))           return stmt;
		if(auto stmt = parse_throw(tokens))            return stmt;
		if(auto stmt = parse_return(tokens))           return stmt;
		if(auto stmt = parse_yield(tokens))            return stmt;
		if(auto stmt = parse_stmt_switch(tokens))      return stmt;
		if(auto stmt = parse_conditional_stmt(tokens)) return stmt;
		auto stmt =  parse_just_an_expr(tokens);
		semicolon(tokens);
		return stmt;
	}
}