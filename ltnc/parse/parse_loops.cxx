#include "parse.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;
	}



	// parses while loop -> while(...)
	ast::stmt_ptr parse_while_loop(Tokens & tokens) {
		if(match(TT::WHILE, tokens)) {
			auto expr = parse_condition(tokens);
			auto body = parse_statement(tokens);
			return std::make_unique<ast::While>(
				std::move(expr),
				std::move(body),
				location(tokens));
		}
		return nullptr;
	}


	// parses while loop -> for i (a, b)
	ast::stmt_ptr parse_for_loop(Tokens & tokens) {
		if(match(TT::FOR, tokens)) {
			if(!match(TT::PAREN_L, tokens)) {
				throw CompilerError{"Expected (", location(tokens)};
			}

			auto var_name = parse_variable_name(tokens);
			auto var = std::make_unique<ast::NewVar>(
				var_name,
				nullptr,
				location(tokens),
				true);

			if(!match(TT::COLON, tokens)) {
				throw CompilerError{"Expected :", location(tokens)};
			}

			auto from = parse_expression(tokens);
			
			if(!match(TT::RARROW, tokens)) {
				throw CompilerError{"Expected ->", location(tokens)};
			}

			auto to = parse_expression(tokens);

			ast::expr_ptr step;
			if(match(TT::COLON, tokens)) {
				step = parse_expression(tokens);
			}

			if(!match(TT::PAREN_R, tokens)) {
				throw CompilerError{"Expected )", location(tokens)};
			}

			auto body = parse_statement(tokens);

			auto loop = std::make_unique<ast::For>(
				std::move(var),
				std::move(from),
				std::move(to),
				std::move(step),
				std::move(body),
				location(tokens)
			);
			return loop;
		}
		return nullptr;
	}
}