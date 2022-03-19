#include "parse.hxx"
#include "ltnc_core/CompilerError.hxx"
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



		// index operator
		template<auto expression_fx>
		std::unique_ptr<ast::Expression> index(lex::Lexer & lexer) {
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
		std::unique_ptr<ast::Expression> postfix(
			lex::Lexer & lexer,
			std::unique_ptr<ast::Expression> l) {

			static constexpr auto postfix_fx = postfix<expression_fx>;
			static constexpr auto index_fx = index<expression_fx>;
			
			if(auto index = index_fx(lexer)) {
				auto full = std::make_unique<ast::Index>(
					std::move(l),
					std::move(index),
					index->location);
				return postfix_fx(lexer, std::move(full));
			}

			auto name = parse::member(lexer);
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
	std::unique_ptr<ast::Expression> prefix(lex::Lexer & lexer) {
		static constexpr auto unary_fx = prefix<primary_fx, expr_fx>;
		// left unary
		const std::array table {
			std::pair{TT::MINUS, OP::NEG},
			std::pair{TT::XMARK, OP::NOT},
			std::pair{TT::QMARK, OP::NUL},
		};
		
		if(auto op = match_op(lexer, table)) {
			auto && r = unary_fx(lexer);
			return std::make_unique<ast::Unary>(*op, std::move(r), lexer.location());
		}
		// right unary
		return postfix<expr_fx>(lexer, primary_fx(lexer));
	}



	std::unique_ptr<ast::Expression> unary(lex::Lexer & lexer) {
		return prefix<parse::primary, parse::expression>(lexer);
	}



	std::unique_ptr<ast::Expression> static_unary(lex::Lexer & lexer) {
		return prefix<parse::static_primary, parse::static_expression>(lexer);
	}
}
