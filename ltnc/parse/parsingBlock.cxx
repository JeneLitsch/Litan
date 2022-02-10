#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	// Block statement between { ... }
	std::unique_ptr<ast::Block> block(lex::Lexer & lexer) {
		if(!lexer.match(TT::BRACE_L)) return nullptr;
		std::vector<std::unique_ptr<ast::Statement>> statements;
		while(!lexer.match(TT::BRACE_R)) {
			if(lexer.match(TT::___EOF___)) {
				throw CompilerError{"missing closing }", lexer.location()}; 
			}
			if(lexer.match(TT::ELSE)) {
				throw CompilerError{"Unexpected else", lexer.location()}; 
			}
			auto stmt = statement(lexer);
			if(stmt) statements.push_back(std::move(stmt));
		}
		return std::make_unique<ast::Block>(
			std::move(statements),
			lexer.location());
	}
}