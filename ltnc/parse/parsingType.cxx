#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		using OP = ltn::c::ast::Unary::Type;
	}

	type::Type container(
		lex::Lexer & lexer, const std::string & name) {
		if(!lexer.match(TT::BRACKET_L)) {
			throw CompilerError("expected [", lexer.inLine());	
		}
		auto && contained = type(lexer);
		if(!lexer.match(TT::BRACKET_R)) {
			throw CompilerError("expected ]", lexer.inLine());
		}
		return type::Type{name, {contained}};
	}

	type::Type type(lex::Lexer & lexer) {
		if(const auto id = lexer.match(TT::INDENTIFIER)) {
			if(id->str == "Array") {
				return container(lexer, "Array");
			}
			return type::Type{id->str};
		}
		else {
			throw CompilerError("expected valid typename", lexer.inLine());
		}
	}
}

