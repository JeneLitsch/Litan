#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
namespace ltn::c {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		using OP = ltn::c::ast::Unary::Type;


		std::optional<std::string> parse_member(lex::Lexer & lexer) {
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



		// index operator
		template<auto expression_fx>
		std::unique_ptr<ast::Expression> parse_index(lex::Lexer & lexer) {
			if(lexer.match(TT::BRACKET_L)) {
				auto index = expression_fx(lexer);
				if(lexer.match(TT::BRACKET_R)) {
					return index;
				}
				throw CompilerError{"Missing ]", lexer.location()};
			}
			return nullptr;
		}



		// recursive right sided unary -> [i]
		template<auto expression_fx>
		std::unique_ptr<ast::Expression> parse_postfix(
			lex::Lexer & lexer,
			std::unique_ptr<ast::Expression> l) {

			static constexpr auto postfix_fx = parse_postfix<expression_fx>;
			static constexpr auto index_fx = parse_index<expression_fx>;
			
			if(auto index = index_fx(lexer)) {
				auto full = std::make_unique<ast::Index>(
					std::move(l),
					std::move(index),
					index->location);
				return postfix_fx(lexer, std::move(full));
			}

			auto name = parse_member(lexer);
			if(name) {
				auto access = std::make_unique<ast::Member>(
					std::move(l),
					*name,
					lexer.location());
				return postfix_fx(lexer, std::move(access));
			}

			return l;
		}
	}



	// Operators - ! [i]
	template<auto primary_fx, auto expr_fx>
	std::unique_ptr<ast::Expression> parse_prefix(lex::Lexer & lexer) {
		static constexpr auto unary_fx = parse_prefix<primary_fx, expr_fx>;
		// left unary
		const std::array table {
			std::pair{TT::MINUS, OP::NEG},
			std::pair{TT::XMARK, OP::NOT},
			std::pair{TT::QMARK, OP::NUL},
			std::pair{TT::TILDE, OP::BITNOT},
		};
		
		if(auto op = match_op(lexer, table)) {
			auto && r = unary_fx(lexer);
			return std::make_unique<ast::Unary>(*op, std::move(r), lexer.location());
		}
		// right unary
		return parse_postfix<expr_fx>(lexer, primary_fx(lexer));
	}



	std::unique_ptr<ast::Expression> parse_unary(lex::Lexer & lexer) {
		return parse_prefix<parse_primary, parse_expression>(lexer);
	}



	std::unique_ptr<ast::Expression> parse_static_unary(lex::Lexer & lexer) {
		return parse_prefix<parse_static_primary, parse_static_expression>(lexer);
	}
}
