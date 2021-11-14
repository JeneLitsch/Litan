#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	std::unique_ptr<ast::Source> source(lex::Lexer & lexer) {
		auto source = std::make_unique<ast::Source>();
		while(!lexer.match(TT::___EOF___)) {
			source->functions.push_back(parse::function(lexer));
		}
		return source;
	}
}