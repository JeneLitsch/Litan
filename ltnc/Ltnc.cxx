#include "Ltnc.hxx"
#include <vector>
#include "lex/Lexer.hxx"
#include "parse/parsing.hxx"
#include "compile/compiling.hxx"

void ltn::c::Ltnc::compile(std::istream & in, const std::string &) {
	std::size_t line = 1;
	std::size_t jumpMarkCounter = 0;
	lex::Lexer lexer{in, line};
	auto source = parse::source(lexer);
	compile::CompilerInfo info {
		this->config,
		this->scope,
		this->fxTable,
		jumpMarkCounter};
	this->buffer << compile::source(*source, info);
}

void ltn::c::Ltnc::yield(std::ostream & out) {
	out << this->buffer.rdbuf();
}
