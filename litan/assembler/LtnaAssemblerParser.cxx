#include "LtnaAssemblerParser.hxx"
#include <sstream>
#include <algorithm>
#include <iostream>

// Split strings into string at a specified delimeter
std::vector<std::string> split(const std::string & str, char delim) {
    std::string line;
    std::vector<std::string> lines;
    std::stringstream ss(str);
    while(std::getline(ss, line, delim)) {
        lines.push_back(line);
    }
    return lines;
}

// Creates a token package of a given instruction
// The first part is the instruction name
// Every subsequent token is an argument
void parseLine(const std::string line, std::uint64_t lineNr, std::vector<ltna::TokenPackage> & tokenPackages) {
	std::vector<std::string> tokens = split(line, ' ');
	
	for(std::string & token : tokens){
		token.erase(std::remove_if(token.begin(), token.end(), isspace), token.end());
	}

	if (tokens.empty()) return;
	if (tokens[0] == "") return;
	else{
		ltna::TokenPackage package(
			line,
			tokens[0],
			std::vector(tokens.begin()+1, tokens.end()),
			lineNr);
		tokenPackages.push_back(package);
	}
}


std::vector<ltna::TokenPackage> ltna::AssemblerParser::parse(const std::string & code) const {
	std::vector<TokenPackage> tokenPackages;
	std::vector<std::string> lines = split(code, '\n');
	std::uint64_t lineNr = 1;
	for(const std::string & line : lines){
		parseLine(line, lineNr, tokenPackages);
		lineNr++;
	}
	return tokenPackages;
}
