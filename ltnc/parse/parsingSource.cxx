#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"
namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	std::unique_ptr<ast::Source> source(lex::Lexer & lexer) {
		std::vector<std::unique_ptr<ast::Function>> functions;
		while(!lexer.match(TT::___EOF___)) {
			if(auto fx = parse::function(lexer)) {
				functions.push_back(std::move(fx));
			}
			else {
				throw CompilerError("Exprected function", lexer.inLine());
			}
		}
		return std::make_unique<ast::Source>(std::move(functions), lexer.debug());
	}
}