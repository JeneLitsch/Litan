#include "parse.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;

		CompilerError invalid_operator(Tokens & tokens) {
			return CompilerError{"Invalid operator", location(tokens)};
		}
	}
	


	MemberCode parse_member_code(Tokens & tokens) {
		if(match(TT::UNDERSCORE, tokens)) {
			if(match(TT::PLUS, tokens) && match(TT::UNDERSCORE, tokens)) {
				return MemberCode::ADD;
			}
			else if(match(TT::MINUS, tokens) && match(TT::UNDERSCORE, tokens)) {
				return MemberCode::SUB;
			}
			else if(match(TT::STAR, tokens) && match(TT::UNDERSCORE, tokens)) {
				return MemberCode::MLT;
			}
			else if(match(TT::SLASH, tokens) && match(TT::UNDERSCORE, tokens)) {
				return MemberCode::DIV;
			}
			else if(match(TT::PERCENT, tokens) && match(TT::UNDERSCORE, tokens)) {
				return MemberCode::MOD;
			}
			else if(match(TT::STARx2, tokens) && match(TT::UNDERSCORE, tokens)) {
				return MemberCode::POW;
			}
		}
		else if(match("str", tokens)) {
			return MemberCode::STR;
		}
		throw invalid_operator(tokens);
	}
}