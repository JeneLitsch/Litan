#include "LtncParser.hxx"
#include <iostream>
#include "LtncParserPackage.hxx"
#include "LtncParserFunctions.hxx"
ltn::c::Parser::Parser() {}


std::unique_ptr<ltn::c::Program> ltn::c::Parser::parse(
	ltn::ErrorReporter & error,
	const std::vector<Token> & tokens) const {

	ParserPackage parsePkg(error, tokens);
	auto program = std::make_unique<Program>();
	while(!parsePkg.isAtEnd()) {
		try {
			parse::declaration(parsePkg, *program);
		}
		catch(const ltn::c::Error & error) {
			parsePkg.error << error;
			parsePkg.resync({ 
				TokenType::FX,
				TokenType::STRUCT,
				TokenType::TYPEDEF});
		} 
	}
	
	return program;
}

