#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	// parses identifier
	std::string indentifier(lex::Lexer & lexer, const std::string & errMsg){
		if(auto token = lexer.match(TT::INDENTIFIER)) {
			return token->str;
		}
		throw ltn::c::CompilerError{errMsg, lexer.inLine()};
	}

	std::string variableName(lex::Lexer & lexer) {
		return indentifier(lexer, "invalid variable name");
	}

	std::string parameterName(lex::Lexer & lexer) {
		return indentifier(lexer, "invalid parameter name");
	}

	std::string functionName(lex::Lexer & lexer) {
		return indentifier(lexer, "invalid function name");
	}
}