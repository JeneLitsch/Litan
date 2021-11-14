#include "Ltnc.hxx"
#include <vector>
#include "lex/Lexer.hxx"
#include "parse/parsing.hxx"
#include "compile/compiling.hxx"

void ltn::c::Ltnc::compile(std::istream & in, const std::string &) {
	std::size_t line = 1;
	lex::Lexer lexer{in, line};
	auto source = parse::source(lexer);
	this->buffer << compile::source(*source, this->config, this->sTable);
}

void ltn::c::Ltnc::yield(std::ostream & out) {
	out << this->buffer.rdbuf();
}
