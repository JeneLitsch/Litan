#include "LtncParserPackage.hxx"
#include <stdexcept>
#include <iostream>

ltnc::ParserPackage::ParserPackage(
	ltn::ErrorReporter & error,
	const std::vector<Token> & tokens)
		: error(error) {
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

bool ltnc::ParserPackage::test(TokenType type) {
	if(this->isAtEnd()) return false;
	if(this->tokens[current].type == type){
		return true;
	}
	return false;
}

bool ltnc::ParserPackage::test(const std::vector<TokenType> types) {
	for(TokenType type : types) {
		if(test(type)) return true;
	}
	return false;
}


void ltnc::ParserPackage::back() {
	this->current--;
}

void ltnc::ParserPackage::advance() {
	this->current++;
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

ltnc::ParserPackage::operator const DebugInfo&() const {
	return this->curr().debugInfo;
}

void ltnc::ParserPackage::resync(const std::vector<TokenType> & tokenTypes) {
	while(true) {
		if(this->isAtEnd()) {
			return;
		}
		for(TokenType type : tokenTypes) {
			if(this->test(type)) {
				return;
			}
		}
		this->advance();
	}
}