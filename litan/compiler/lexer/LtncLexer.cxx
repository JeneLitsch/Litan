#include "LtncLexer.hxx"

ltnc::Lexer::Lexer() {

}


std::vector<ltnc::Token> ltnc::Lexer::tokenize(const std::string & str) {
	typedef LexerNodeCreator LNC;
	LexerNode tree = LNC::connector({
		LNC::chr('!', {
			LNC::chr('=', TokenType::UNEQUAL)
		}),
		LNC::chr('=', TokenType::ASSIGN, {
			LNC::chr('=', TokenType::EQUAL)
		}),
		LNC::chr('>', TokenType::BIGGER, {
			LNC::chr('=', TokenType::BIGGEREQUAL)
		}),
		LNC::chr('<', TokenType::SMALLER, {
			LNC::chr('=', TokenType::SMALLEREQUAL)
		}),

		LNC::chr(';', TokenType::SEMICOLON),
		LNC::chr(',', TokenType::COMMA),
		
		LNC::chr('{', TokenType::L_BRACE),
		LNC::chr('}', TokenType::R_BRACE),
		LNC::chr('(', TokenType::L_PARAN),
		LNC::chr(')', TokenType::R_PARAN),

		LNC::chr('+', TokenType::PLUS),
		LNC::chr('-', TokenType::MINUS, {
			LNC::numliteral(),
			LNC::chr('>', TokenType::CALL),
		}),
		LNC::chr('*', TokenType::STAR),
		LNC::chr('%', TokenType::MOD),
		LNC::chr('/', TokenType::SLASH, {
			LNC::chr('/', {
				LNC::ignoreLine()
			}),
		}),

		LNC::newLine(),
		LNC::ignore('\t'),
		LNC::ignore(' '),
		LNC::identifier(),
		LNC::numliteral(),

	});


	LexerPackage lexPkg(str);
	while (!lexPkg.isAtEnd()) {
		this->process(lexPkg, tree);
	}
	return lexPkg.getTokens();
}




void ltnc::Lexer::process(LexerPackage & lexPkg, LexerNode & tree) {
	lexPkg.sync();
	if(tree.eval(lexPkg)) {
		return;
	}
	else {
		lexPkg.error("Error: Unknown token: " + lexPkg.makeLexeme(), lexPkg);
	}
}

