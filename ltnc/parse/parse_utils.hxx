#pragma once
#include <functional>
#include <vector>
#include "ltnc/ast/AST.hxx"
#include "ltnc/tokens/Token.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	template<typename Elem>
	inline auto list_of(
		Token::Type end,
		std::string end_str,
		Tokens & tokens,
		auto parse_elem) {

		std::vector<Elem> elements;
		
		while(true) {
			if(match(Token::Type::___EOF___, tokens)) throw CompilerError{
				end_str, location(tokens)
			};
			elements.push_back(parse_elem(tokens));
			// Last comma is optional
			// A missing last comma is not an error if ] follows
			const auto comma = match(Token::Type::COMMA, tokens);
			if(match(end, tokens)) return elements;
			// Only throw on missings commas in case of an unclosed array
			if(!comma) throw CompilerError{
				"Expected ,", location(tokens)
			};
		}
	}



	auto match_op(
		Tokens & tokens,
		const auto & op_table) -> std::optional<decltype(op_table.front().second)> {
		for(const auto & [tt, op] : op_table) {
			if(match(tt, tokens)) {
				return op;
			}
		}
		return std::nullopt;
	}
}