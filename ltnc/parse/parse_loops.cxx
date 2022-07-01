#include "parse.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}



	// parses while loop -> while(...)
	ast::stmt_ptr parse_while_loop(lex::Lexer & lexer) {
		if(lexer.match(TT::WHILE)) {
			auto expr = parse_condition(lexer);
			auto body = parse_statement(lexer);
			return std::make_unique<ast::While>(
				std::move(expr),
				std::move(body),
				lexer.location());
		}
		return nullptr;
	}


	// parses while loop -> for i (a, b)
	ast::stmt_ptr parse_for_loop(lex::Lexer & lexer) {
		if(lexer.match(TT::FOR)) {
			if(!lexer.match(TT::PAREN_L)) {
				throw CompilerError{"Expected (", lexer.location()};
			}

			auto var_name = parse_variable_name(lexer);
			auto var = std::make_unique<ast::NewVar>(
				var_name,
				nullptr,
				lexer.location(),
				true);

			if(!lexer.match(TT::COLON)) {
				throw CompilerError{"Expected :", lexer.location()};
			}

			auto from = parse_expression(lexer);
			
			if(!lexer.match(TT::RARROW)) {
				throw CompilerError{"Expected ->", lexer.location()};
			}

			auto to = parse_expression(lexer);

			ast::expr_ptr step;
			if(lexer.match(TT::COLON)) {
				step = parse_expression(lexer);
			}

			if(!lexer.match(TT::PAREN_R)) {
				throw CompilerError{"Expected )", lexer.location()};
			}

			auto body = parse_statement(lexer);

			auto loop = std::make_unique<ast::For>(
				std::move(var),
				std::move(from),
				std::move(to),
				std::move(step),
				std::move(body),
				lexer.location()
			);
			return loop;
		}
		return nullptr;
	}
}