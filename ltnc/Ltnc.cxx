#include "Ltnc.hxx"
#include <vector>
#include "lex/Lexer.hxx"
#include "parse/parsing.hxx"
#include "compile/compiling.hxx"

void ltn::c::Ltnc::compile(std::istream & in, const std::string &) {

	lex::Lexer lexer{in, this->line};
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
