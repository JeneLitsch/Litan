#include "Ltnc.hxx"
#include <vector>
#include "lex/Lexer.hxx"
#include "parse/parsing.hxx"

void ltn::c::Ltnc::compile(std::istream & in, const std::string &) {

	lex::Lexer lexer{in, this->line};
	auto source = parse::source(lexer);
	this->backend->compile(this->config, *source);
}

void ltn::c::Ltnc::yield(std::ostream & out) {
	this->backend->yield(out);
}
