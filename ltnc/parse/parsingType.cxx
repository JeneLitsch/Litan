#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
#include "ltn/Loop.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		using OP = ltn::c::ast::Unary::Type;
	}

	void openBracket(lex::Lexer & lexer) {
		if(!lexer.match(TT::BRACKET_L)) {
			throw CompilerError("expected [", lexer.inLine());	
		}
	}

	void closeBracket(lex::Lexer & lexer) {
		if(!lexer.match(TT::BRACKET_R)) {
			if(lexer.match(TT::COMMA)) {
				throw CompilerError("Too many subtypes.", lexer.inLine());
			}
			throw CompilerError("expected ]", lexer.inLine());
		}
	}

	std::vector<type::Type> subtypes(lex::Lexer & lexer, std::size_t subtypeCount) {
		std::vector<type::Type> contained;
		repeat_1st(subtypeCount, [&] (bool first) {
			if(!first) {
				
				if(lexer.match(TT::BRACKET_R)) {
					std::stringstream ss;
					ss 	<< "Map expects " << subtypeCount << " subtypes. "
						<< contained.size() << " given.";
					throw CompilerError{ ss.str(), lexer.inLine()};
				}
				
				if(!lexer.match(TT::COMMA)) {
					throw CompilerError{
						"Expected comma between types",
						lexer.inLine()};
				}
			}
			contained.push_back(parse::type(lexer));
		});
		return contained;
	}

	type::Type container(lex::Lexer & lexer, const std::string & name, std::size_t subtypeCount) {
		openBracket(lexer);
		auto && contained = subtypes(lexer, subtypeCount);
		closeBracket(lexer);
		return type::Type{name, std::move(contained)};
	}

	type::Type type(lex::Lexer & lexer) {
		if(const auto id = lexer.match(TT::INDENTIFIER)) {
			if(id->str == "Array") 	return container(lexer, id->str, 1);
			if(id->str == "Map") 	return container(lexer, id->str, 2);
			if(id->str == "Stack") 	return container(lexer, id->str, 1);
			return type::Type{id->str};
		}
		else {
			throw CompilerError("expected valid typename", lexer.inLine());
		}
	}
}

