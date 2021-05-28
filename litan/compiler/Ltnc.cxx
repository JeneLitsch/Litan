#include "Ltnc.hxx"
#include <iostream>
#include "LtncLexer.hxx"
#include "LtncParser.hxx"
#include "LtncCompiler.hxx"

std::string ltnc::LTNC::compile(
	const std::string & source,
	bool comments,
	bool silent,
	unsigned optimizationLevel) const {

	ltnc::Lexer lexer;
	ltnc::Parser parser;
	ltnc::Compiler compiler;

	if(!silent) std::cout << ">> Tokenization..." << std::endl;
	auto tokens = lexer.tokenize(source);
	if(!silent) std::cout << ">> Parsing..." << std::endl;
	auto ast = parser.parse(tokens);
	if(!silent) std::cout << ">> Compiling..." << std::endl;
	auto asmb = compiler.compile(ast, optimizationLevel, comments);
	if(!silent) std::cout << ">> Done compiling code!" << std::endl;
	std::cout << std::endl;
	return asmb;

}