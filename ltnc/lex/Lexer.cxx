#include "Lexer.hxx"
#include "lexing.hxx"

ltnc::lex::Lexer::Lexer(std::istream & in, std::size_t & line)
	:	in(in), line(line) {}

std::optional<ltnc::lex::Token> ltnc::lex::Lexer::match(Token::Type type) {
	if(!this->token) {
		this->token = lex::token(in, line);
	}

	if(this->token->type == type) {
		const auto t = this->token;
		this->token = {};
		return t;
	}
	return {};
}
