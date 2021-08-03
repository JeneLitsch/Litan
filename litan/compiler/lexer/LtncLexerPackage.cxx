#include "LtncLexerPackage.hxx"
#include <stdexcept>
#include "LtncErrorHandling.hxx"
ltnc::LexerPackage::LexerPackage(const std::string & code) {
	this->string = code;
	this->line = 1;
	this->start = 0;
	this->current = 0;
	this->column = 0;
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
		this->next();
		return true;
	}
	return false;
}

bool ltnc::LexerPackage::matchAlpha(){
	if(this->isAtEnd()) return false;
	if(std::isalpha(this->string[current])) {
		this->next();
		return true;
	}
	return false;
}
bool ltnc::LexerPackage::matchDigit(){
	if(this->isAtEnd()) return false;
	if(std::isdigit(this->string[current])) {
		this->next();
		return true;
	}
	return false;
}


void ltnc::LexerPackage::newLine() {
	this->line++;
	this->column = 0;
}

void ltnc::LexerPackage::sync() {
	this->start = this->current;
}

void ltnc::LexerPackage::next() {
	this->current++;
	this->column++;
}

void ltnc::LexerPackage::newToken(TokenType type) {
	this->newToken(type, this->makeLexeme());
}

void ltnc::LexerPackage::newToken(TokenType type, const std::string & lexeme) {
	TokenDebugInfo debugInfo(line, column, lexeme);
	this->addToken(Token(type, lexeme, debugInfo));
}

void ltnc::LexerPackage::addToken(Token token) {
	this->tokens.push_back(token);
}

const std::vector<ltnc::Token> ltnc::LexerPackage::getTokens() const {
	return this->tokens;
}

std::nullptr_t ltnc::LexerPackage::error(const std::string & msg) {
	throw std::runtime_error(
		"Lexer-Error: " + msg + 
		" in line " + std::to_string(this->line) + 
		" in column " + std::to_string(this->column) + 
		" at " + this->getTokens().back().string);
}