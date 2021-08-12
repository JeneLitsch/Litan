#include "LtncParser.hxx"
#include <iostream>
#include "LtncParserPackage.hxx"
#include "LtncParserFunctions.hxx"
ltnc::Parser::Parser() {}


std::shared_ptr<ltnc::Program> ltnc::Parser::parse(
	ltn::ErrorReporter & error,
	const std::vector<Token> & tokens) const {

	ParserPackage parsePkg(error, tokens);
	auto program = std::make_shared<Program>();
	while(!parsePkg.isAtEnd()) {
		try {
			parse::declaration(parsePkg, *program);
		}
		catch(const ltnc::Error & error) {
			parsePkg.error << error;
			parsePkg.resync({ 
				TokenType::FX,
				TokenType::STRUCT,
				TokenType::TYPEDEF});
		} 
	}
	
	return program;
}

