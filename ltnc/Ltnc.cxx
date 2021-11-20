#include "Ltnc.hxx"
#include <vector>
#include "lex/Lexer.hxx"
#include "parse/parsing.hxx"
#include "compile/compiling.hxx"
#include "compile/Instructions.hxx"

void ltn::c::Ltnc::compile(std::istream & in, const std::string &) {

	lex::Lexer lexer{in, this->line};
	auto source = parse::source(lexer);
	compile::CompilerInfo info {
		this->config,
		this->fxTable,
		jumpMarkCounter};
	this->buffer << compile::source(*source, info);
}

void ltn::c::Ltnc::yield(std::ostream & out) {
	if(const auto fxmain = this->fxTable.find("main", 0)) {
		out	<< compile::inst::call(fxmain->id) 
			<< compile::inst::exlt
			<< "\n";
		out << this->buffer.rdbuf();
	}
	else {
		throw CompilerError {"main() is undefined", 0};
	}
}
