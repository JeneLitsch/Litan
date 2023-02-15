#include "parse.hxx"
#include "parse_utils.hxx"
#include "stdxx/array.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;
		
		
		
		ast::Expression single_element_tuple(ast::Expression first, const Token & start) {
			std::vector<ast::Expression> elements;
			elements.push_back(std::move(first));
			return std::make_unique<ast::Tuple>(
				start.location,
				std::move(elements)
			);
		}



		ast::Expression multi_element_tuple(ast::Expression first, Tokens & tokens, const Token & start) {
			auto elements = list_of<ast::Expression>(TT::PAREN_R, ")", tokens, parse_expression);
			elements.insert(std::begin(elements), std::move(first));
			return std::make_unique<ast::Tuple>(
				start.location,
				std::move(elements)
			);
		}



		ast::Expression parse_tuple(ast::Expression first, Tokens & tokens, const Token & start) {
			if(match(TT::PAREN_R, tokens)) {
				return single_element_tuple(std::move(first), start);
			}
			return multi_element_tuple(std::move(first), tokens, start);
		}
	}
	
	

	ast::Expression parse_parenthesized(Tokens & tokens) {
		if(auto start = match(TT::PAREN_L, tokens)) {
			auto expr = parse_expression(tokens);
			if(match(TT::PAREN_R, tokens)) {
				return expr;
			}
			if(match(TT::COMMA, tokens)) {
				return parse_tuple(std::move(expr), tokens, *start);
			}
			throw CompilerError{
				"Expected tuple list or )",
				start->location
			};
		}
		return ast::Expression();
	}
}
