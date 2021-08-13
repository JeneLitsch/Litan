#include "LtncLexer.hxx"
#include "LtncError.hxx"
#include "LtncErrorCreationLexer.hxx"

ltn::c::Lexer::Lexer() {}


std::vector<ltn::c::Token> ltn::c::Lexer::tokenize(
	const std::string & source,
	const std::string & sourceName) {
	typedef LexerNodeCreator LNC;
	// create lexing tree
	LexerNode tree = LNC::connector({
		LNC::chr('!', TokenType::LOG_NOT, { 
			LNC::chr('=', TokenType::UNEQUAL),
		}),
		LNC::chr('~', TokenType::BIT_NOT),
		LNC::chr('=', TokenType::ASSIGN, {
			LNC::chr('=', TokenType::EQUAL)
		}),
		LNC::chr('>', TokenType::BIGGER, {
			LNC::chr('=', TokenType::BIGGEREQUAL)
		}),
		LNC::chr('<', TokenType::SMALLER, {
			LNC::chr('=', TokenType::SMALLEREQUAL, {
				LNC::chr('>', TokenType::SPACESHIP)
			})
		}),

		LNC::chr('&', TokenType::BIT_AND, {
			LNC::chr('&', TokenType::LOG_AND)
		}),
		LNC::chr('|', TokenType::BIT_OR, {
			LNC::chr('|', TokenType::LOG_OR)
		}),


		LNC::chr(';', TokenType::SEMICOLON),
		LNC::chr(',', TokenType::COMMA),
		LNC::chr('.', TokenType::DOT),
		LNC::chr(':', {
			LNC::chr(':', TokenType::DOUBLE_COLON) 
		}),
		
		LNC::chr('{', TokenType::L_BRACE),
		LNC::chr('}', TokenType::R_BRACE),
		LNC::chr('(', TokenType::L_PAREN),
		LNC::chr(')', TokenType::R_PAREN),

		LNC::chr('+', TokenType::PLUS),
		LNC::chr('-', TokenType::MINUS, {
			LNC::chr('>', TokenType::ARROW),
		}),
		LNC::chr('*', TokenType::STAR),
		LNC::chr('%', TokenType::MOD),
		LNC::chr('/', TokenType::SLASH, {
			LNC::chr('/', {
				LNC::ignoreLine()
			}),
		}),
		LNC::chr('^', TokenType::POWER),

		LNC::string(),
		LNC::newLine(),
		LNC::ignore('\t'),
		LNC::ignore(' '),
		LNC::identifier(),
		LNC::numliteral(),

	});

	// run until end of string
	LexerPackage lexPkg(source, sourceName);
	while (!lexPkg.isAtEnd()) {
		this->process(lexPkg, tree);
	}
	return lexPkg.getTokens();
}




void ltn::c::Lexer::process(LexerPackage & lexPkg, LexerNode & tree) {
	lexPkg.sync();
	if(tree.eval(lexPkg)) {
		return;
	}
	else {
		throw error::invalidToken(lexPkg.makeDebugInfo(), lexPkg.makeLexeme());
	}
}

