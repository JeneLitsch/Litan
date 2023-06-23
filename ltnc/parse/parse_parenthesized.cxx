#include "parse.hxx"
#include "parse_utils.hxx"
#include "stdxx/array.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;
		
		
		
		ast::expr_ptr single_element_tuple(ast::expr_ptr first, const Token & start) {
			std::vector<ast::expr_ptr> elements;
			elements.push_back(std::move(first));
			return std::make_unique<ast::Tuple>(
				start.location,
				std::move(elements)
			);
		}



		ast::expr_ptr multi_element_tuple(ast::expr_ptr first, Tokens & tokens, const Token & start) {
			auto elements = list_of<ast::expr_ptr>(TT::PAREN_R, ")", tokens, parse_expression);
			elements.insert(std::begin(elements), std::move(first));
			return std::make_unique<ast::Tuple>(
				start.location,
				std::move(elements)
			);
		}



		ast::expr_ptr parse_tuple(ast::expr_ptr first, Tokens & tokens, const Token & start) {
			if(match(TT::PAREN_R, tokens)) {
				return single_element_tuple(std::move(first), start);
			}
			return multi_element_tuple(std::move(first), tokens, start);
		}
	}
	
	

	ast::expr_ptr parse_parenthesized(const Token & start, Tokens & tokens) {
		if(match(TT::PAREN_R, tokens)) {
			return std::make_unique<ast::Tuple>(start.location);
		}
		auto expr = parse_expression(tokens);
		if(match(TT::PAREN_R, tokens)) {
			return expr;
		}
		if(match(TT::COMMA, tokens)) {
			return parse_tuple(std::move(expr), tokens, start);
		}
		throw CompilerError{
			"Expected tuple list or )",
			start.location
		};
	}
}
