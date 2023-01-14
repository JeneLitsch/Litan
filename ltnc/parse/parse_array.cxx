#include "parse.hxx"

namespace ltn::c {
	using TT = Token::Type;

	namespace {
		ast::litr_ptr parse_empty_array(Tokens & tokens) {
			return stx::make_unique<ast::Array>(location(tokens));
		}



		ast::litr_ptr parse_filled_array(Tokens & tokens) {
			auto array = stx::make_unique<ast::Array>(location(tokens));
			array->elements = parse_list(TT::BRACKET_R, "]", tokens);
			return array;
		}
	}



	ast::litr_ptr parse_array(Tokens & tokens) {
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