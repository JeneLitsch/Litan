#include "parse.hxx"
#include "ltnc_core/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}



	// parses while loop -> while(...)
	ast::stmt_ptr while_loop(lex::Lexer & lexer) {
		if(lexer.match(TT::WHILE)) {
			auto expr = condition(lexer);
			auto body = statement(lexer);
			return std::make_unique<ast::While>(
				std::move(expr),
				std::move(body),
				lexer.location());
		}
		return nullptr;
	}



	// parses while loop -> for i (a, b)
	ast::stmt_ptr for_loop(lex::Lexer & lexer) {
		if(lexer.match(TT::FOR)) {
			if(!lexer.match(TT::PAREN_L)) {
				throw CompilerError{"Expected (", lexer.location()};
			}

			auto var_name = variable_name(lexer);
			auto var = std::make_unique<ast::NewConst>(
				var_name,
				nullptr,
				lexer.location());

			if(!lexer.match(TT::COLON)) {
				throw CompilerError{"Expected :", lexer.location()};
			}

			auto from = expression(lexer);
			
			if(!lexer.match(TT::RARROW)) {
				throw CompilerError{"Expected ->", lexer.location()};
			}

			auto to = expression(lexer);

			ast::expr_ptr step;
			if(lexer.match(TT::COLON)) {
				step = expression(lexer);
			}

			bool reverse = false;
			bool closed = false;
			while(auto t = lexer.match(TT::INDENTIFIER)) {
				if(t->str == "reverse") {
					reverse = true;
				}
				else if(t->str == "closed") {
					closed = true;
				}
				else {
					throw CompilerError{"Unknown loop tag: " + t->str, lexer.location()};
				}
			}
		
			if(!lexer.match(TT::PAREN_R)) {
				throw CompilerError{"Expected )", lexer.location()};
			}

			auto body = statement(lexer);

			auto loop = std::make_unique<ast::For>(
				std::move(var),
				std::move(from),
				std::move(to),
				std::move(step),
				std::move(body),
				lexer.location()
			);

			loop->reverse = reverse;
			loop->closed = closed;

			return loop;
		}
		return nullptr;
	}
}