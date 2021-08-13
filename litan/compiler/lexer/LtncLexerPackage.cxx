#include "LtncLexerPackage.hxx"
#include <stdexcept>
#include "LtncError.hxx"
#include "LtncErrorCreationLexer.hxx"

ltn::c::LexerPackage::LexerPackage(
	const std::string & source,
	const std::string & sourceName) {
	this->source = source;
	this->sourceName = sourceName;
	this->line = 1;
	this->start = 0;
	this->current = 0;
	this->column = 0;
}

bool ltn::c::LexerPackage::isAtEnd() const {
	return this->current >= this->source.size();
}

std::string ltn::c::LexerPackage::makeLexeme() const {
	return this->source.substr(this->start, this->current - this->start);
}

ltn::c::DebugInfo ltn::c::LexerPackage::makeDebugInfo() const {
	return this->makeDebugInfo(this->makeLexeme());
}

ltn::c::DebugInfo ltn::c::LexerPackage::makeDebugInfo(const std::string & str) const {
	return DebugInfo(line, column, str, sourceName);
}

bool ltn::c::LexerPackage::match(char chr) {
	if(this->isAtEnd()) return false;
	if(this->source[current] == chr) {
		this->next();
		return true;
	}
	return false;
}

bool ltn::c::LexerPackage::matchAlpha(){
	if(this->isAtEnd()) return false;
	if(std::isalpha(this->source[current])) {
		this->next();
		return true;
	}
	return false;
}
bool ltn::c::LexerPackage::matchDigit(){
	if(this->isAtEnd()) return false;
	if(std::isdigit(this->source[current])) {
		this->next();
		return true;
	}
	return false;
}


void ltn::c::LexerPackage::newLine() {
	this->line++;
	this->column = 0;
}

void ltn::c::LexerPackage::sync() {
	this->start = this->current;
}

void ltn::c::LexerPackage::next() {
	this->current++;
	this->column++;
}

void ltn::c::LexerPackage::newToken(TokenType type) {
	this->newToken(type, this->makeLexeme());
}

void ltn::c::LexerPackage::newToken(TokenType type, const std::string & lexeme) {
	this->addToken(Token(type, lexeme, this->makeDebugInfo(lexeme)));
}

void ltn::c::LexerPackage::addToken(Token token) {
	this->tokens.push_back(token);
}

const std::vector<ltn::c::Token> ltn::c::LexerPackage::getTokens() const {
	return this->tokens;
}

std::nullptr_t ltn::c::LexerPackage::error(const std::string & msg) {
	throw std::runtime_error(
		"Lexer-Error: " + msg + 
		" in line " + std::to_string(this->line) + 
		" in column " + std::to_string(this->column) + 
		" at " + this->getTokens().back().string);
}