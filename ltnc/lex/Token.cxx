#include "Token.hxx"
namespace ltn::c::lex {
	const Token Token::end = Token{Token::Type::___EOF___, "___EOF___", SourceLocation{}};
}
