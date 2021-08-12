#include "Ltnc.hxx"
#include <iostream>
#include "LtncLexer.hxx"
#include "LtncParser.hxx"
#include "LtncCompiler.hxx"
#include "LtnFileIO.hxx"
#include "LtncStructurePrinter.hxx"

std::vector<ltnc::Ltnc::SourcePair> includeStdLib(
	const std::vector<ltnc::Ltnc::SourcePair> & sources_,
	const std::string & stdPath) {
	
	std::vector<ltnc::Ltnc::SourcePair> sources = sources_;
	std::vector<std::string> libFiles = {
		"/basic.ltn",
		"/math.ltn",
		"/array.ltn",
		"/sort.ltn",
		"/stack.ltn",
		"/queue.ltn",
		"/deque.ltn",
		"/io.ltn",
		"/exept.ltn",
		"/string.ltn"}; 
	
	for(const std::string & file : libFiles) {
		auto filepath = stdPath + file; 
		sources.push_back({filepath, ltn::readFile(filepath)});
	}
	
	return sources;
}

std::vector<ltnc::Token> tokenize(
	const std::vector<ltnc::Ltnc::SourcePair> & sources) {
	ltnc::Lexer lexer;
	std::vector<ltnc::Token> tokens;
	for(const ltnc::Ltnc::SourcePair & source : sources) {
		auto newTokens = lexer.tokenize(source.source, source.sourceName);
		tokens.reserve(tokens.size() + newTokens.size());
		for(const auto & token : newTokens) {
			tokens.push_back(token);
		}
	}
	return tokens;
}

std::string ltnc::Ltnc::compile(
	const std::vector<SourcePair> & sources_,
	const CompilerSettings & settings,
	bool silent,
	bool print) const {

	ltnc::Parser parser;
	ltnc::Compiler compiler;
	ltn::ErrorReporter error;


	if(!silent) {
		std::cout << ">> Including standard library..." << std::endl;
	}
	auto sources = includeStdLib(sources_, settings.getStdlibPath());


	if(!silent) {
		std::cout << ">> Tokenization..." << std::endl;
	}
	auto tokens = tokenize(sources);


	if(!silent) {
		std::cout << ">> Parsing..." << std::endl;
	}
	auto ast = parser.parse(error, tokens);


	if(!silent) {
		std::cout << ">> Compiling..." << std::endl;
	}
	auto asmb = compiler.compile(ast, error, settings);
	
	if(error.throwable()) {
		throw error;
	}

	if(!silent) {
		std::cout << ">> Done compiling code!" << std::endl;
	}


	if(!silent && print) {
		std::cout 
			<< "All Symbols" << "\n"
			<< StructurePrinter(*ast) << std::endl;
	}


	std::cout << std::endl;
	return asmb;
}