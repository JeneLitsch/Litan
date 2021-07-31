#include "LtnaAssemblerParser.hxx"
#include <sstream>
#include <algorithm>
#include <iostream>

std::vector<ltna::TokenPackage> ltna::AssemblerParser::parse(const std::string & code) const {
	std::vector<TokenPackage> tokenPackages;
	std::vector<std::string> lines = this->split(code, '\n');
	for(const std::string & line : lines){
		this->parseLine(line, tokenPackages);
	}
	return tokenPackages;
}

void ltna::AssemblerParser::parseLine(const std::string line, std::vector<TokenPackage> & tokenPackages) const{
	std::vector<std::string> tokens = this->split(line, ' ');
	
	for(std::string & token : tokens){
		token.erase(std::remove_if(token.begin(), token.end(), isspace), token.end());
	}

	if (tokens.empty()) return;
	if (tokens[0] == "") return;
	else{
		TokenPackage package(line, tokens[0], std::vector(tokens.begin()+1, tokens.end()));
		tokenPackages.push_back(package);
	}
}

// split strings into string at a given delimeter
std::vector<std::string> ltna::AssemblerParser::split(const std::string & str, char delim) const{
    std::string line;
    std::vector<std::string> lines;
    std::stringstream ss(str);
    while(std::getline(ss, line, delim)) {
        lines.push_back(line);
    }
    return lines;
}