#include "parse.hxx"
#include "litan_compiler/CompilerError.hxx"
#include "litan_compiler/ast/stmt/Block.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;
	}

	// Block statement between { ... }
	ast::stmt_ptr parse_block(Tokens & tokens) {
		if(!match(TT::BRACE_L, tokens)) return nullptr;
		std::vector<ast::stmt_ptr> statements;
		while(!match(TT::BRACE_R, tokens)) {
			if(match(TT::___EOF___, tokens)) {
				throw CompilerError{"missing closing }", location(tokens)}; 
			}
			if(match(TT::ELSE, tokens)) {
				throw CompilerError{"Unexpected else", location(tokens)}; 
			}
			statements.push_back(parse_statement(tokens));
		}
		return ast::stmt::block(std::move(statements), location(tokens));
	}
}