#include "parse.hxx"
#include "ltnc_core/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	// parses identifier
	std::string indentifier(lex::Lexer & lexer, const std::string & errMsg){
		if(auto token = lexer.match(TT::INDENTIFIER)) {
			return token->str;
		}
		throw ltn::c::CompilerError{errMsg, lexer.location()};
	}

	std::string preset_name(lex::Lexer & lexer) {
		return indentifier(lexer, "invalid preset name");
	}

	std::string enum_name(lex::Lexer & lexer) {
		return indentifier(lexer, "invalid preset name");
	}

	std::string definition(lex::Lexer & lexer) {
		return indentifier(lexer, "invalid definition name");
	}

	std::string variable_name(lex::Lexer & lexer) {
		return indentifier(lexer, "invalid variable name");
	}

	std::string parameter_name(lex::Lexer & lexer) {
		return indentifier(lexer, "invalid parameter name");
	}

	std::string function_name(lex::Lexer & lexer) {
		return indentifier(lexer, "invalid function name");
	}
}