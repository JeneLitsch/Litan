#include "parse.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;
		
		
		
		ast::expr_ptr single_element_tuple(ast::expr_ptr first, const Token & start) {
			auto tuple = std::make_unique<ast::Tuple>(start.location);
			tuple->elements.push_back(std::move(first));
			return tuple;
		}



		ast::expr_ptr multi_element_tuple(ast::expr_ptr first, Tokens & tokens, const Token & start) {
			auto tuple = std::make_unique<ast::Tuple>(start.location);
			tuple->elements = parse_list(TT::PAREN_R, ")", tokens, std::move(first));
			return tuple;
		}



		ast::expr_ptr parse_tuple(ast::expr_ptr first, Tokens & tokens, const Token & start) {
			if(match(TT::PAREN_R, tokens)) {
				return single_element_tuple(std::move(first), start);
			}
			return multi_element_tuple(std::move(first), tokens, start);
		}
	}
	
	

	ast::expr_ptr parse_parenthesized(Tokens & tokens) {
		if(auto start = match(TT::PAREN_L, tokens)) {
			auto expr = parse_expression(tokens);
			if(match(TT::PAREN_R, tokens)) {
				return expr;
			}
			if(match(TT::COMMA, tokens)) {
				return parse_tuple(std::move(expr), tokens, *start);
			}
			else {
				throw CompilerError{
					"Expected tuple list or )",
					start->location};
				
			}
		}
		return nullptr;
	}
}
