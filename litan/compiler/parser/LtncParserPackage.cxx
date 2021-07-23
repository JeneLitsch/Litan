#include "LtncParserPackage.hxx"
#include <stdexcept>
#include <iostream>

ltnc::ParserPackage::ParserPackage(const std::vector<Token> & tokens) {
	this->current = 0;
	this->tokens = tokens;
}

// internals
bool ltnc::ParserPackage::match(TokenType type){
	if(this->isAtEnd()) return false;
	if(this->tokens[current].type == type){
		this->current++;
		return true;
	}
	return false;
}

void ltnc::ParserPackage::back() {
	std::cout << this->current << std::endl;
	this->current--;
}

bool ltnc::ParserPackage::match(const std::vector<TokenType> types) {
	for(TokenType type : types) {
		if(match(type)) return true;
	}
	return false;
}

bool ltnc::ParserPackage::isAtEnd() const{
	return this->current >= this->tokens.size();
}

const ltnc::Token & ltnc::ParserPackage::prev() const {
	return this->tokens[this->current-1];
}

const ltnc::Token & ltnc::ParserPackage::curr() const {
	return this->tokens[this->current];
}

std::nullptr_t ltnc::ParserPackage::error(const std::string & msg) {
	throw std::runtime_error("Parsing-Error: " + msg + " in line " + std::to_string(this->curr().line) + " at " + this->curr().string);
}