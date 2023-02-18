#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
#include "parse_utils.hxx"
namespace ltn::c {
	namespace {
		using TT = Token::Type;
		using OP = UnaryOp;



		std::string parse_member(Tokens & tokens) {
			if(auto member = match(TT::INDENTIFIER, tokens)) {
				return member->str;
			}
			else {
				throw CompilerError {
					"Expected identifier for member access",
					location(tokens)
				};
			}
		}



		std::unique_ptr<ast::Expression> parse_index(Tokens & tokens) {
			auto index = parse_expression(tokens);
			if(match(TT::BRACKET_R, tokens)) {
				return index;
			}
			throw CompilerError{"Missing ]", location(tokens)};
		}



		auto parse_arguments(Tokens & tokens) {
			std::vector<ast::expr_ptr> function_arguments;
			std::vector<type::IncompleteType> template_arguments;
			if(match(TT::PAREN_R, tokens)) {
				return std::make_pair(
					std::move(function_arguments),
					std::move(template_arguments)
				);
			}
			while(true) {
				if(match(TT::SMALLER, tokens)) {
					BraceTracker brace_tracker;
					brace_tracker.open();
					template_arguments.push_back(parse_type(tokens, brace_tracker));
					close_chevron(tokens, brace_tracker);
					brace_tracker.finalize();
				}
				else {
					function_arguments.push_back(parse_expression(tokens));
				}
				if(match(TT::PAREN_R, tokens)) {
					return std::make_pair(
						std::move(function_arguments),
						std::move(template_arguments)
					);
				}
				if(!match(TT::COMMA, tokens)) throw CompilerError {
					"Expected ,", location(tokens)
				};
			}
		}



		ast::expr_ptr parse_call(
			Tokens & tokens,
			std::unique_ptr<ast::Expression> l) {
			
			auto [function_args, template_args] = parse_arguments(tokens); 

			auto call = stx::make_unique<ast::Call>(
				std::move(l),
				std::move(function_args),
				location(tokens)
			);
			
			call->template_arguments = template_args;

			return call;
		}



		std::unique_ptr<ast::Expression> parse_postfix(
			Tokens & tokens,
			std::unique_ptr<ast::Expression> l) {

			if(auto start = match(TT::BRACKET_L, tokens)) {
				auto index = parse_index(tokens);
				auto location = ast::location(*index);
				auto full = stx::make_unique<ast::Index>(
					std::move(l),
					std::move(index),
					location
				);
				return parse_postfix(tokens, std::move(full));
			}

			if(auto start = match(TT::DOT, tokens)) {
				auto name = parse_member(tokens);
				auto access = stx::make_unique<ast::Member>(
					std::move(l),
					name,
					location(tokens)
				);
				return parse_postfix(tokens, std::move(access));
			}

			if(auto start = match(TT::PAREN_L, tokens)) {
				auto call = parse_call(tokens, std::move(l));
				return parse_postfix(tokens, std::move(call));
			}

			return l;
		}
	}



	std::tuple<std::vector<type::IncompleteType>, bool> 
	parse_template_args(Tokens & tokens){
		std::vector<type::IncompleteType> template_args;

		while(auto token = match(TT::SMALLER, tokens)) {
			BraceTracker brace_tracker;
			brace_tracker.open();
			template_args.push_back(parse_type(tokens, brace_tracker));
			close_chevron(tokens, brace_tracker);
			brace_tracker.finalize();
			
			if(match(TT::PAREN_R, tokens)) {
				return {std::move(template_args), true};
			}
			if(!match(TT::COMMA, tokens)) {
				throw CompilerError{ "Expected ,", location(tokens) };
			}
		}
	
		return {std::move(template_args), false};
	}



	std::unique_ptr<ast::Expression> parse_prefix(Tokens & tokens) {
		// left unary
		const std::array table {
			std::pair{TT::MINUS, OP::NEG},
			std::pair{TT::XMARK, OP::NOT},
			std::pair{TT::QMARK, OP::NUL},
			std::pair{TT::TILDE, OP::BITNOT},
			std::pair{TT::STAR,  OP::DEREF},
		};
		
		if(auto op = match_op(tokens, table)) {
			auto && r = parse_prefix(tokens);
			return stx::make_unique<ast::Unary>(*op, std::move(r), location(tokens));
		}
		return parse_postfix(tokens, parse_primary(tokens));
	}



	std::unique_ptr<ast::Expression> parse_unary(Tokens & tokens) {
		return parse_prefix(tokens);
	}
}
