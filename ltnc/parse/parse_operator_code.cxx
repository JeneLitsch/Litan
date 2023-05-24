#include "parse.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;

		CompilerError invalid_operator(Tokens & tokens) {
			return CompilerError{"Invalid operator", location(tokens)};
		}
	}
	


	OperatorCode parse_operator_code(Tokens & tokens) {
		if(match(TT::UNDERSCORE, tokens)) {
			if(match(TT::PLUS, tokens) && match(TT::UNDERSCORE, tokens)) {
				return OperatorCode::ADD;
			}
			else if(match(TT::MINUS, tokens) && match(TT::UNDERSCORE, tokens)) {
				return OperatorCode::SUB;
			}
			else if(match(TT::STAR, tokens)) {
				if(match(TT::STAR, tokens) && match(TT::UNDERSCORE, tokens)) {
					return OperatorCode::POW;
				}
				else if(match(TT::UNDERSCORE, tokens)) {
					return OperatorCode::MLT;
				}
				throw invalid_operator(tokens);
			}
			else if(match(TT::SLASH, tokens) && match(TT::UNDERSCORE, tokens)) {
				return OperatorCode::DIV;
			}
			else if(match(TT::PERCENT, tokens) && match(TT::UNDERSCORE, tokens)) {
				return OperatorCode::MOD;
			}
		}
		throw invalid_operator(tokens);
	}
}