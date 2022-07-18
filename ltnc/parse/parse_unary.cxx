#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
namespace ltn::c {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		using OP = ltn::c::ast::Unary::Type;


		std::optional<std::string> parse_member(Tokens & tokens) {
			if(match(TT::DOT, tokens)) {
				if(auto member = match(TT::INDENTIFIER, tokens)) {
					return member->str;
				}
				else {
					throw CompilerError{
						"Expected identifier for member access",
						tokens.location()};
				}
			}
			return std::nullopt;
		}



		// index operator
		template<auto expression_fx>
		std::unique_ptr<ast::Expression> parse_index(Tokens & tokens) {
			if(match(TT::BRACKET_L, tokens)) {
				auto index = expression_fx(tokens);
				if(match(TT::BRACKET_R, tokens)) {
					return index;
				}
				throw CompilerError{"Missing ]", tokens.location()};
			}
			return nullptr;
		}



		// recursive right sided unary -> [i]
		template<auto expression_fx>
		std::unique_ptr<ast::Expression> parse_postfix(
			Tokens & tokens,
			std::unique_ptr<ast::Expression> l) {

			static constexpr auto postfix_fx = parse_postfix<expression_fx>;
			static constexpr auto index_fx = parse_index<expression_fx>;
			
			if(auto index = index_fx(tokens)) {
				auto full = std::make_unique<ast::Index>(
					std::move(l),
					std::move(index),
					index->location);
				return postfix_fx(tokens, std::move(full));
			}

			auto name = parse_member(tokens);
			if(name) {
				auto access = std::make_unique<ast::Member>(
					std::move(l),
					*name,
					tokens.location());
				return postfix_fx(tokens, std::move(access));
			}

			return l;
		}
	}



	// Operators - ! [i]
	template<auto primary_fx, auto expr_fx>
	std::unique_ptr<ast::Expression> parse_prefix(Tokens & tokens) {
		static constexpr auto unary_fx = parse_prefix<primary_fx, expr_fx>;
		// left unary
		const std::array table {
			std::pair{TT::MINUS, OP::NEG},
			std::pair{TT::XMARK, OP::NOT},
			std::pair{TT::QMARK, OP::NUL},
			std::pair{TT::TILDE, OP::BITNOT},
		};
		
		if(auto op = match_op(tokens, table)) {
			auto && r = unary_fx(tokens);
			return std::make_unique<ast::Unary>(*op, std::move(r), tokens.location());
		}
		// right unary
		return parse_postfix<expr_fx>(tokens, primary_fx(tokens));
	}



	std::unique_ptr<ast::Expression> parse_unary(Tokens & tokens) {
		return parse_prefix<parse_primary, parse_expression>(tokens);
	}



	std::unique_ptr<ast::Expression> parse_static_unary(Tokens & tokens) {
		return parse_prefix<parse_static_primary, parse_static_expression>(tokens);
	}
}
