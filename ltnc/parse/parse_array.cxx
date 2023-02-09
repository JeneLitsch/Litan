#include "parse.hxx"

namespace ltn::c {
	using TT = Token::Type;

	namespace {
		ast::expr_ptr parse_empty_array(Tokens & tokens) {
			return std::make_unique<ast::Array>(
				location(tokens),
				std::vector<ast::expr_ptr>{}
			);
		}



		auto parse_members(
			TT end,
			std::string end_str,
			Tokens & tokens) {
				
			std::vector<std::pair<std::string, ast::expr_ptr>> elements;

			while(true) {
				if(match(TT::___EOF___, tokens)) {
					throw CompilerError{end_str, location(tokens)};
				}
				if(!match(TT::DOT, tokens)) {
					throw CompilerError{"Expected . (dot)", location(tokens)};
				}
				auto name = parse_variable_name(tokens);
				if(!match(TT::ASSIGN, tokens)) {
					throw CompilerError{"Expected =", location(tokens)};
				}
				auto expr = parse_expression(tokens);
				elements.push_back({std::move(name), std::move(expr)});
				// Last comma is optional
				// A missing last comma is not an error if ] follows
				const bool comma = static_cast<bool>(match(TT::COMMA, tokens));
				if(match(end, tokens)) {
					return elements;
				}
				// Only throw on missings commas in case of an unclosed array
				if(!comma) {
					throw CompilerError{"Expected ,", location(tokens)};
				} 
			}
		}


		ast::expr_ptr parse_struct_init(Tokens & tokens) {
			auto init_struct = std::make_unique<ast::InitStruct>(location(tokens));
			init_struct->members = parse_members(TT::BRACKET_R, "]", tokens);
			return init_struct;
		}



		ast::expr_ptr parse_filled_array(Tokens & tokens) {
			auto elements = parse_list(TT::BRACKET_R, "]", tokens);
			return std::make_unique<ast::Array>(
				location(tokens),
				std::move(elements)
			);
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
			else {
				return parse_filled_array(tokens);
			}
		}
		return nullptr;
	}
}