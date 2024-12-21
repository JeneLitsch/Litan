#include "parse.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	using TT = Token::Type;
	std::string parse_member(Tokens & tokens) {
		// if(auto code = parse_reserved_member_name(tokens)) {
		// 	return *code;
		// }
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