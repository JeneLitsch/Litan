#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		using OP = ltn::c::ast::Unary::Type;


		std::optional<std::string> member(lex::Lexer & lexer) {
			if(lexer.match(TT::DOT)) {
				if(auto member = lexer.match(TT::INDENTIFIER)) {
					return member->str;
				}
				else {
					throw CompilerError{
						"Expected identifier for member access",
						lexer.location()};
				}
			}
			return std::nullopt;
		}


		// recursive right sided unary -> [i]
		std::unique_ptr<ast::Expression> postfix(
			lex::Lexer & lexer,
			std::unique_ptr<ast::Expression> l) {
			
			if(auto index = parse::index(lexer)) {
				auto full = std::make_unique<ast::Index>(
					std::move(l),
					std::move(index),
					index->location);
				return postfix(lexer, std::move(full));
			}

			auto name = parse::member(lexer);
			if(name) {
				auto access = std::make_unique<ast::Member>(
					std::move(l),
					*name,
					lexer.location());
				return postfix(lexer, std::move(access));
			}

			return l;
		}
	}

	// index operator
	std::unique_ptr<ast::Expression> index(lex::Lexer & lexer) {
		if(lexer.match(TT::BRACKET_L)) {
			auto index = expression(lexer);
			if(lexer.match(TT::BRACKET_R)) {
				return index;
			}
			throw CompilerError{"Missing ]", lexer.location()};
		}
		return nullptr;
	}

	// Operators - ! [i]
	std::unique_ptr<ast::Expression> unary(lex::Lexer & lexer) {
		// left unary
		const std::array table {
			std::pair{TT::MINUS, OP::NEG},
			std::pair{TT::XMARK, OP::NOT},
			std::pair{TT::QMARK, OP::NUL},
		};
		for(auto [tt, op] : table) {
			if(lexer.match(tt)) {
				auto && r = unary(lexer);
				return std::make_unique<ast::Unary>(op, std::move(r), lexer.location());
			}
		}
		// right unary
		return postfix(lexer, parse::primary(lexer));
	}
}