#include "LtncLexerPackage.hxx"
#include <stdexcept>
#include "LtncError.hxx"
#include "LtncErrorCreationLexer.hxx"

ltnc::LexerPackage::LexerPackage(
	const std::string & source,
	const std::string & sourceName) {
	this->source = source;
	this->sourceName = sourceName;
	this->line = 1;
	this->start = 0;
	this->current = 0;
	this->column = 0;
}

bool ltnc::LexerPackage::isAtEnd() const {
	return this->current >= this->source.size();
}

std::string ltnc::LexerPackage::makeLexeme() const {
	return this->source.substr(this->start, this->current - this->start);
}

ltnc::DebugInfo ltnc::LexerPackage::makeDebugInfo() const {
	return this->makeDebugInfo(this->makeLexeme());
}

ltnc::DebugInfo ltnc::LexerPackage::makeDebugInfo(const std::string & str) const {
	return DebugInfo(line, column, str, sourceName);
}

bool ltnc::LexerPackage::match(char chr) {
	if(this->isAtEnd()) return false;
	if(this->source[current] == chr) {
		this->next();
		return true;
	}
	return false;
}

bool ltnc::LexerPackage::matchAlpha(){
	if(this->isAtEnd()) return false;
	if(std::isalpha(this->source[current])) {
		this->next();
		return true;
	}
	return false;
}
bool ltnc::LexerPackage::matchDigit(){
	if(this->isAtEnd()) return false;
	if(std::isdigit(this->source[current])) {
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
	this->addToken(Token(type, lexeme, this->makeDebugInfo(lexeme)));
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