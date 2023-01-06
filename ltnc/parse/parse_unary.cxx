#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
namespace ltn::c {
	namespace {
		using TT = Token::Type;
		using OP = ltn::c::ast::Unary::Type;



		std::optional<std::string> parse_member(Tokens & tokens) {
			if(match(TT::DOT, tokens)) {
				if(auto member = match(TT::INDENTIFIER, tokens)) {
					return member->str;
				}
				else {
					throw CompilerError{
						"Expected identifier for member access",
						location(tokens)};
				}
			}
			return std::nullopt;
		}



		template<auto expression_fx>
		std::unique_ptr<ast::Expression> parse_index(Tokens & tokens) {
			if(match(TT::BRACKET_L, tokens)) {
				auto index = expression_fx(tokens);
				if(match(TT::BRACKET_R, tokens)) {
					return index;
				}
				throw CompilerError{"Missing ]", location(tokens)};
			}
			return nullptr;
		}



		auto parse_arguments(Tokens & tokens) {
			std::vector<std::unique_ptr<ast::Expression>> parameters;
			if(match(TT::PAREN_R, tokens)) {
				 return parameters;
			}
			while(true) {
				parameters.push_back(parse_expression(tokens));
				if(match(TT::PAREN_R, tokens)) {
					return parameters;
				}
				if(!match(TT::COMMA, tokens)) throw CompilerError {
					"Expected ,", location(tokens)
				};
			}
		}



		template<auto expression_fx>
		std::unique_ptr<ast::Expression> parse_postfix(
			Tokens & tokens,
			std::unique_ptr<ast::Expression> l) {

			static constexpr auto postfix_fx = parse_postfix<expression_fx>;
			static constexpr auto index_fx = parse_index<expression_fx>;
			
			if(auto index = index_fx(tokens)) {
				auto full = stx::make_unique<ast::Index>(
					std::move(l),
					std::move(index),
					index->location);
				return postfix_fx(tokens, std::move(full));
			}

			auto name = parse_member(tokens);
			if(name) {
				auto access = stx::make_unique<ast::Member>(
					std::move(l),
					*name,
					location(tokens));
				return postfix_fx(tokens, std::move(access));
			}

			if(auto begin = match(TT::PAREN_L, tokens)) {

				auto [template_args, done] = parse_template_args(tokens); 
				std::vector<ast::expr_ptr> function_args; 
				if(!done) {
					function_args = parse_arguments(tokens);
				}
				
				auto call = stx::make_unique<ast::Call>(
					std::move(l),
					std::move(function_args),
					location(tokens)
				);
				call->template_args = template_args;
				return postfix_fx(tokens, std::move(call));
			}

			return l;
		}
	}



	std::tuple<std::vector<type::IncompleteType>, bool>
	parse_template_args(Tokens & tokens){
		std::vector<type::IncompleteType> template_args;
		bool done = false;

		while(auto token = match(TT::SMALLER, tokens)) {
			BraceTracker brace_tracker;
			brace_tracker.open();
			template_args.push_back(parse_type(tokens, brace_tracker));
			close_chevron(tokens, brace_tracker);
			brace_tracker.finalize();
			if(match(TT::PAREN_R, tokens)) {
				done = true;
				break;
			}
			if(match(TT::COMMA, tokens)) {
				if(match(TT::PAREN_R, tokens)) throw CompilerError{
					"Unexpected )", location(tokens)
				};
			}
		}
	
		return {std::move(template_args), done};
	}



	template<auto primary_fx, auto expr_fx>
	std::unique_ptr<ast::Expression> parse_prefix(Tokens & tokens) {
		static constexpr auto unary_fx = parse_prefix<primary_fx, expr_fx>;
		// left unary
		const std::array table {
			std::pair{TT::MINUS, OP::NEG},
			std::pair{TT::XMARK, OP::NOT},
			std::pair{TT::QMARK, OP::NUL},
			std::pair{TT::TILDE, OP::BITNOT},
			std::pair{TT::STAR,  OP::DEREF},
		};
		
		if(auto op = match_op(tokens, table)) {
			auto && r = unary_fx(tokens);
			return stx::make_unique<ast::Unary>(*op, std::move(r), location(tokens));
		}
		return parse_postfix<expr_fx>(tokens, primary_fx(tokens));
	}



	std::unique_ptr<ast::Expression> parse_unary(Tokens & tokens) {
		return parse_prefix<parse_primary, parse_expression>(tokens);
	}
}
