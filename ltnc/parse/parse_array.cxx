#include "parse.hxx"
#include "parse_utils.hxx"
#include "ltn/MemberCode.hxx"

namespace ltn::c {
	using TT = Token::Type;

	namespace {
		ast::expr_ptr parse_empty_array(Tokens & tokens) {
			return std::make_unique<ast::expr::Array>(
				location(tokens),
				std::vector<ast::expr_ptr>{}
			);
		}



		auto parse_member(Tokens & tokens) {


			if(match(TT::BRACE_L, tokens)) {
				MemberCode code = parse_member_code(tokens);

				if(!match(TT::BRACE_R, tokens)) {
					throw CompilerError{"Expected }", location(tokens)};
				}

				if(!match(TT::ASSIGN, tokens)) {
					throw CompilerError{"Expected =", location(tokens)};
				}
				auto expr = parse_expression(tokens);

				return ast::expr::Struct::Member{
					.name = code,
					.expr = std::move(expr),
				};
			}
			else {
				auto name = parse_variable_name(tokens);
				if(!match(TT::ASSIGN, tokens)) {
					throw CompilerError{"Expected =", location(tokens)};
				}
				auto expr = parse_expression(tokens);

				return ast::expr::Struct::Member{
					.name = std::move(name),
					.expr = std::move(expr),
				};
			}
		}


		ast::expr_ptr parse_struct_init(Tokens & tokens) {
			auto init_struct = std::make_unique<ast::expr::Struct>(location(tokens));
			if(!match(TT::DOT, tokens)) {
				throw CompilerError{"Expected . (dot)", location(tokens)};
			}
			if(match(TT::BRACKET_R, tokens)) {
				return init_struct;
			}
			bool first = true;
			init_struct->members = list_of<ast::expr::Struct::Member>(TT::BRACKET_R, "]", tokens, [&] (auto & t) {
				if(!std::exchange(first, false) && !match(TT::DOT, t)) {
					throw CompilerError{"Expected . (dot)", location(t)};
				}
				return parse_member(t);
			});
			return init_struct;
		}



		ast::expr_ptr parse_single_element_array(ast::expr_ptr only, Tokens & tokens) {
			std::vector<ast::expr_ptr> elements;
			elements.push_back(std::move(only));
			return std::make_unique<ast::expr::Array>(
				location(tokens),
				std::move(elements)
			);
		}



		ast::expr_ptr parse_multi_element_array(ast::expr_ptr first, Tokens & tokens) {
			std::vector<ast::expr_ptr> elements;
			elements.push_back(std::move(first));
			if(!match(TT::BRACKET_R, tokens)) {
				elements += list_of<ast::expr_ptr>(TT::BRACKET_R, "]", tokens, parse_expression);
			}
			return std::make_unique<ast::expr::Array>(
				location(tokens),
				std::move(elements)
			);
		}



		ast::expr_ptr parse_empty_map(Tokens & tokens) {
			if(!match(TT::BRACKET_R, tokens)) {
				throw CompilerError { "Expected ]", location(tokens) };
			}
			return std::make_unique<ast::expr::Map>(location(tokens));
		}



		std::unique_ptr<ast::expr::Map> parse_single_pair_map(
			ast::expr_ptr first_key,
			ast::expr_ptr first_val,
			Tokens & tokens) {
			auto map = std::make_unique<ast::expr::Map>(location(tokens));
			map->pairs.push_back(ast::expr::Map::Pair {
				.key = std::move(first_key), 
				.val = std::move(first_val),
			});
			return map;
		}



		ast::expr_ptr parse_multi_pair_map(
			ast::expr_ptr first_key,
			ast::expr_ptr first_val,
			Tokens & tokens) {
			auto map = parse_single_pair_map(std::move(first_key), std::move(first_val), tokens);
			map->pairs += list_of<ast::expr::Map::Pair>(TT::BRACKET_R, "]", tokens, [&] (auto &) {
				ast::expr_ptr key = parse_expression(tokens);
				if(!match(TT::COLON, tokens)) {
					throw CompilerError { "Expected :", location(tokens) };
				}
				ast::expr_ptr val = parse_expression(tokens);
				return ast::expr::Map::Pair {
					.key = std::move(key), 
					.val = std::move(val),
				};
			});

			return map;
		}



		ast::expr_ptr parse_map(ast::expr_ptr first_key, Tokens & tokens) {
			ast::expr_ptr first_val = parse_expression(tokens);

			if(match(TT::BRACKET_R, tokens)) {
				return parse_single_pair_map(std::move(first_key), std::move(first_val), tokens);
			}
			else if(match(TT::COMMA, tokens)) {
				return parse_multi_pair_map(std::move(first_key), std::move(first_val), tokens);
			}
			else {
 				throw CompilerError { "Expected ,", location(tokens) };
			}
		}



		ast::expr_ptr parse_filled_array(Tokens & tokens) {
			auto first = parse_expression(tokens);
			if(match(TT::BRACKET_R, tokens)) {
				return parse_single_element_array(std::move(first), tokens);
			} 
			else if(match(TT::COMMA, tokens)) {
				return parse_multi_element_array(std::move(first), tokens);
			}
			else if(match(TT::COLON, tokens)) {
				return parse_map(std::move(first), tokens);
			}
			else {
 				throw CompilerError { "Expected ,", location(tokens) };
			}
		}
	}



	ast::expr_ptr parse_array(Tokens & tokens) {
		if(match(TT::BRACKET_L, tokens)) {
			if(match(TT::BRACKET_R, tokens)) {
				return parse_empty_array(tokens);
			}
			else if(check(TT::DOT, tokens)) {
				return parse_struct_init(tokens);
			}
			else if(match(TT::COLON, tokens)) {
				return parse_empty_map(tokens);
			}
			else {
				return parse_filled_array(tokens);
			}
		}
		return nullptr;
	}
}