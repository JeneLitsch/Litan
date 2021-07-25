#include "Ltnc.hxx"
#include <iostream>
#include "LtncLexer.hxx"
#include "LtncParser.hxx"
#include "LtncCompiler.hxx"
#include "LtnFileIO.hxx"
#include "LtncStructurePrinter.hxx"
std::string ltnc::Ltnc::compile(
	const std::string & source,
	const CompilerSettings & settings,
	bool silent,
	bool print) const {

	ltnc::Lexer lexer;
	ltnc::Parser parser;
	ltnc::Compiler compiler;



	std::string code = source 
		+ ltn::readFile(settings.getStdlibPath() + "/basic.ltn") 
		+ ltn::readFile(settings.getStdlibPath() + "/math.ltn") 
		+ ltn::readFile(settings.getStdlibPath() + "/array.ltn") 
		+ ltn::readFile(settings.getStdlibPath() + "/io.ltn") 
		+ ltn::readFile(settings.getStdlibPath() + "/exept.ltn")
		+ ltn::readFile(settings.getStdlibPath() + "/string.ltn");

	if(!silent) std::cout << ">> Tokenization..." << std::endl;
	auto tokens = lexer.tokenize(code);
	if(!silent) std::cout << ">> Parsing..." << std::endl;
	auto ast = parser.parse(tokens);
	if(!silent) std::cout << ">> Compiling..." << std::endl;
	auto asmb = compiler.compile(ast, settings);
	if(!silent && print) {
		std::cout << StructurePrinter(*ast) << std::endl;
	}
	if(!silent) std::cout << ">> Done compiling code!" << std::endl;
	std::cout << std::endl;
	return asmb;

}