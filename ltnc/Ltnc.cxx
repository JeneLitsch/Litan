#include "Ltnc.hxx"
#include <vector>
#include "lex/Lexer.hxx"
#include "parse/parsing.hxx"

void ltnc::Ltnc::compile(std::istream & in, const std::string &) {
	std::size_t line = 1;
	std::vector<std::unique_ptr<ast::Function>> functions;
	lex::Lexer lexer{in, line};
	while(!in.eof()) {
		functions.push_back(parse::function(lexer));
	}
}

void ltnc::Ltnc::yield(std::ostream & out) {
	out << "Hello World\n";
}
