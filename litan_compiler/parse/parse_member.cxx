#include "parse.hxx"
#include "litan_compiler/CompilerError.hxx"

namespace ltn::c {
	using TT = Token::Type;
	std::string parse_member(Tokens & tokens) {
		if(auto member = match(TT::INDENTIFIER, tokens)) {
			return member->str;
		}
		else {
			throw CompilerError {
				"Expected identifier for member access",
				location(tokens)
			};
		}
	}
}