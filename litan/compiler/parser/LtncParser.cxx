#include "LtncParser.hxx"
#include <iostream>
#include "LtncParserPackage.hxx"
#include "LtncParserFunctions.hxx"
ltnc::Parser::Parser() {}


std::shared_ptr<ltnc::Program> ltnc::Parser::parse(const std::vector<Token> & tokens) const {
	ParserPackage parsePkg(tokens);
	auto program = std::make_shared<Program>();
	while(!parsePkg.isAtEnd()) {
		parse::declaration(parsePkg, *program);
	}
	return program;
}

