#include "LtncParserPackage.hxx"
#include <stdexcept>
#include <iostream>

ltn::c::ParserPackage::ParserPackage(
	ltn::ErrorReporter & error,
	const std::vector<Token> & tokens)
		: error(error) {
	this->current = 0;
	this->tokens = tokens;
}

// internals
bool ltn::c::ParserPackage::match(TokenType type){
	if(this->isAtEnd()) return false;
	if(this->tokens[current].type == type){
		this->current++;
		return true;
	}
	return false;
}

bool ltn::c::ParserPackage::test(TokenType type) {
	if(this->isAtEnd()) return false;
	if(this->tokens[current].type == type){
		return true;
	}
	return false;
}

bool ltn::c::ParserPackage::test(const std::vector<TokenType> types) {
	for(TokenType type : types) {
		if(test(type)) return true;
	}
	return false;
}


void ltn::c::ParserPackage::back() {
	this->current--;
}

void ltn::c::ParserPackage::advance() {
	this->current++;
}

bool ltn::c::ParserPackage::match(const std::vector<TokenType> types) {
	for(TokenType type : types) {
		if(match(type)) return true;
	}
	return false;
}

bool ltn::c::ParserPackage::isAtEnd() const{
	return this->current >= this->tokens.size();
}

const ltn::c::Token & ltn::c::ParserPackage::prev() const {
	return this->tokens[this->current-1];
}

const ltn::c::Token & ltn::c::ParserPackage::curr() const {
	return this->tokens[this->current];
}

ltn::c::ParserPackage::operator const DebugInfo&() const {
	return this->curr().debugInfo;
}

void ltn::c::ParserPackage::resync(const std::vector<TokenType> & tokenTypes) {
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