#include "parse.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	// parses identifier
	std::string parse_indentifier(lex::Lexer & lexer, const std::string & errMsg){
		if(auto token = lexer.match(TT::INDENTIFIER)) {
			return token->str;
		}
		throw ltn::c::CompilerError{errMsg, lexer.location()};
	}

	std::string parse_preset_name(lex::Lexer & lexer) {
		return parse_indentifier(lexer, "invalid preset name");
	}

	std::string parse_enum_name(lex::Lexer & lexer) {
		return parse_indentifier(lexer, "invalid preset name");
	}

	std::string parse_definition(lex::Lexer & lexer) {
		return parse_indentifier(lexer, "invalid definition name");
	}

	std::string parse_variable_name(lex::Lexer & lexer) {
		return parse_indentifier(lexer, "invalid variable name");
	}

	std::string parse_parameter_name(lex::Lexer & lexer) {
		return parse_indentifier(lexer, "invalid parameter name");
	}

	std::string parse_function_name(lex::Lexer & lexer) {
		return parse_indentifier(lexer, "invalid function name");
	}
}