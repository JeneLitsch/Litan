#include "LtncLexerPackage.hxx"
#include <stdexcept>
ltnc::LexerPackage::LexerPackage(const std::string & code) {
	this->string = code;
	this->line = 1;
	this->start = 0;
	this->current = 0;
}

bool ltnc::LexerPackage::isAtEnd() const {
	return this->current >= this->string.size();
}

std::string ltnc::LexerPackage::makeLexeme() const {
	return this->string.substr(this->start, this->current - this->start);

}

bool ltnc::LexerPackage::match(char chr) {
	if(this->isAtEnd()) return false;
	if(this->string[current] == chr) {
		this->current++;
		return true;
	}
	return false;
}

bool ltnc::LexerPackage::matchAlpha(){
	if(this->isAtEnd()) return false;
	if(std::isalpha(this->string[current])) {
		this->current++;
		return true;
	}
	return false;
}
bool ltnc::LexerPackage::matchDigit(){
	if(this->isAtEnd()) return false;
	if(std::isdigit(this->string[current])) {
		this->current++;
		return true;
	}
	return false;
}


void ltnc::LexerPackage::newLine() {
	this->line++;
}

void ltnc::LexerPackage::sync() {
	this->start = this->current;
}

void ltnc::LexerPackage::next() {
	this->current++;
}

unsigned ltnc::LexerPackage::getLine() const {
	return this->line;
}

void ltnc::LexerPackage::newToken(TokenType type) {
	this->tokens.push_back(Token(type, this->makeLexeme(), line));
}

const std::vector<ltnc::Token> ltnc::LexerPackage::getTokens() const {
	return this->tokens;
}

std::nullptr_t ltnc::LexerPackage::error(const std::string & msg, LexerPackage & lexPkg) {
	throw std::runtime_error("Lexer-Error: " + msg + " in line " + std::to_string(lexPkg.getLine()) + " at " + lexPkg.getTokens().back().string);
}