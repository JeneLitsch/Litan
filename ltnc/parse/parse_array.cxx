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
			else {
				return parse_filled_array(tokens);
			}
		}
		return nullptr;
	}
}