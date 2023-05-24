#include "parse.hxx"
#include "parse_utils.hxx"
#include "ltn/OperatorCode.hxx"

namespace ltn::c {
	using TT = Token::Type;

	namespace {
		ast::expr_ptr parse_empty_array(Tokens & tokens) {
			return std::make_unique<ast::Array>(
				location(tokens),
				std::vector<ast::expr_ptr>{}
			);
		}



		CompilerError invalid_operator(Tokens & tokens) {
			return CompilerError{"Invalid operator", location(tokens)};
		}



		OperatorCode parse_operator_code(Tokens & tokens) {
			if(match(TT::UNDERSCORE, tokens)) {
				if(match(TT::PLUS, tokens) && match(TT::UNDERSCORE, tokens)) {
					return OperatorCode::ADD;
				}
				else if(match(TT::MINUS, tokens) && match(TT::UNDERSCORE, tokens)) {
					return OperatorCode::SUB;
				}
				else if(match(TT::STAR, tokens)) {
					if(match(TT::STAR, tokens) && match(TT::UNDERSCORE, tokens)) {
						return OperatorCode::POW;
					}
					else if(match(TT::UNDERSCORE, tokens)) {
						return OperatorCode::MLT;
					}
					throw invalid_operator(tokens);
				}
				else if(match(TT::SLASH, tokens) && match(TT::UNDERSCORE, tokens)) {
					return OperatorCode::DIV;
				}
				else if(match(TT::PERCENT, tokens) && match(TT::UNDERSCORE, tokens)) {
					return OperatorCode::MOD;
				}
			}
			throw invalid_operator(tokens);
		}



		auto parse_member(Tokens & tokens) {
			if(!match(TT::DOT, tokens)) {
				throw CompilerError{"Expected . (dot)", location(tokens)};
			}

			if(match(TT::BRACE_L, tokens)) {
				OperatorCode code = parse_operator_code(tokens);

				if(!match(TT::BRACE_R, tokens)) {
					throw CompilerError{"Expected }", location(tokens)};
				}

				if(!match(TT::ASSIGN, tokens)) {
					throw CompilerError{"Expected =", location(tokens)};
				}
				auto expr = parse_expression(tokens);

				return ast::InitStruct::Member{
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

				return ast::InitStruct::Member{
					.name = std::move(name),
					.expr = std::move(expr),
				};
			}
		}


		ast::expr_ptr parse_struct_init(Tokens & tokens) {
			auto init_struct = std::make_unique<ast::InitStruct>(location(tokens));
			init_struct->members = list_of<ast::InitStruct::Member>(TT::BRACKET_R, "]", tokens, parse_member);
			return init_struct;
		}



		ast::expr_ptr parse_filled_array(Tokens & tokens) {
			auto elements = list_of<ast::expr_ptr>(TT::BRACKET_R, "]", tokens, parse_expression);
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