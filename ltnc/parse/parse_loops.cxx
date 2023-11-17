#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/ast/stmt/ForEach.hxx"
#include "ltnc/ast/stmt/While.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;
	}



	ast::stmt_ptr parse_while_loop(Tokens & tokens) {
		if(match(TT::WHILE, tokens)) {
			auto expr = parse_condition(tokens);
			auto body = parse_statement(tokens);
			return ast::stmt::while_loop(
				std::move(expr),
				std::move(body),
				location(tokens)
			);
		}
		return nullptr;
	}



	ast::stmt_ptr parse_for_loop(Tokens & tokens) {
		if(auto start = match(TT::FOR, tokens)) {
			if(!match(TT::PAREN_L, tokens)) {
				throw CompilerError{"Expected (", location(tokens)};
			}

			auto var_name = parse_variable_name(tokens);

			if(!match(TT::COLON, tokens)) {
				throw CompilerError{"Expected :", location(tokens)};
			}


			auto from = parse_expression(tokens);

			if(!match(TT::PAREN_R, tokens)) {
				throw CompilerError{"Expected )", location(tokens)};
			}
			
			auto body = parse_statement(tokens);
			return ast::stmt::for_each(
				var_name,
				std::move(from),
				std::move(body),
				start->location
			);
		}
		return nullptr;
	}
}