#include "parse.hxx"

namespace ltn::c {
	using TT = Token::Type;
	
	std::vector<ast::expr_ptr> parse_list(
		TT end,
		std::string end_str,
		Tokens & tokens,
		ast::expr_ptr first) {
			
		std::vector<ast::expr_ptr> elements;
		if(first) {
			elements.push_back(std::move(first));
		}			

		while(true) {
			if(match(TT::___EOF___, tokens)) {
				throw CompilerError{end_str, location(tokens)};
			}
			elements.push_back(parse_expression(tokens));
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
}