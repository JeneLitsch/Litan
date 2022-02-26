#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	// parses while loop -> while(...)
	std::unique_ptr<ast::While> while_loop(lex::Lexer & lexer) {
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
	std::unique_ptr<ast::For> for_loop(lex::Lexer & lexer) {
		if(lexer.match(TT::FOR)) {
			auto var_name = variable_name(lexer);
			auto var = std::make_unique<ast::NewVar>(
				var_name,
				nullptr,
				lexer.location());
			if(lexer.match(TT::PAREN_L)) {
				auto from = expression(lexer);
				if(lexer.match(TT::COMMA)) {
					auto to = expression(lexer);
					if(lexer.match(TT::PAREN_R)) {
						auto body = statement(lexer);
						return std::make_unique<ast::For>(
							std::move(var),
							std::move(from),
							std::move(to),
							std::move(body),
							lexer.location()
						);
					}
					throw CompilerError{"Expected )", lexer.location()};
				}
				throw CompilerError{"Expected ,", lexer.location()};
			}
			throw CompilerError{"Expected (", lexer.location()};
		}
		return nullptr;
	}
}