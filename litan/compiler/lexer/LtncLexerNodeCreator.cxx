#include "LtncLexerNodeCreator.hxx"
#include <map>

ltnc::LexerNode ltnc::LexerNodeCreator::chr(char chr, std::vector<LexerNode> nodes) {
	return LexerNode([chr, nodes](LexerPackage & lexPkg) {
		if(lexPkg.match(chr))  {
			for(const LexerNode & node : nodes) {
				if(node.eval(lexPkg)) {
					return true;
				}
			}
		}
		return false;
	});
}

ltnc::LexerNode ltnc::LexerNodeCreator::chr(char chr, TokenType type) {
	return LexerNode([chr, type](LexerPackage & lexPkg) {
		if(lexPkg.match(chr))  {
			lexPkg.newToken(type);
			return true;
		}
		return false;
	});
}

ltnc::LexerNode ltnc::LexerNodeCreator::chr(char chr, TokenType type, std::vector<LexerNode> nodes) {
	return LexerNode([chr, nodes, type](LexerPackage & lexPkg) {
		if(lexPkg.match(chr))  {
			for(const LexerNode & node : nodes) {
				if(node.eval(lexPkg)) {
					return true;
				}
			}
			lexPkg.newToken(type);
			return true;
		}
		return false;
	});
}

ltnc::LexerNode ltnc::LexerNodeCreator::connector(std::vector<LexerNode> nodes) {
	return LexerNode([nodes](LexerPackage & lexPkg) {
		for(const LexerNode & node : nodes) {
			if(node.eval(lexPkg)) {
				return true;
			}
		}
		return false;
	});
}

ltnc::LexerNode ltnc::LexerNodeCreator::ignoreLine() {
	return LexerNode([](LexerPackage & lexPkg) {
		while (!lexPkg.isAtEnd()){
			if(lexPkg.match('\n')) {
				lexPkg.newLine();
				break;
			} 
			lexPkg.next();
		}
		return true;
	});
}

ltnc::LexerNode ltnc::LexerNodeCreator::newLine() {
	return LexerNode([](LexerPackage & lexPkg) {
		if(lexPkg.match('\n'))  {
			lexPkg.newLine();
			return true;
		}
		return false;
	});
}

ltnc::LexerNode ltnc::LexerNodeCreator::ignore(char chr) {
	return LexerNode([chr](LexerPackage & lexPkg) {
		if(lexPkg.match(chr))  {
			return true;
		}
		return false;
	});
}

ltnc::LexerNode ltnc::LexerNodeCreator::numliteral() {
	return LexerNode([](LexerPackage & lexPkg) {
		if(lexPkg.matchDigit()) {
			bool isFloat = false;
			while(!lexPkg.isAtEnd() && lexPkg.matchDigit());
			if(lexPkg.match('.')) {
				isFloat = true;
				while(!lexPkg.isAtEnd() && lexPkg.matchDigit());
			}
			std::string lexeme = lexPkg.makeLexeme();
			TokenType type = isFloat ? TokenType::FLOAT_LITERAL : TokenType::INT_LITERAL;
			lexPkg.newToken(type);
			return true;
		}
		return false;
	});
}

ltnc::LexerNode ltnc::LexerNodeCreator::identifier() {
	std::map<std::string, TokenType> keywords;
	keywords.insert({"typedef", TokenType::TYPEDEF});
	keywords.insert({"var", TokenType::VAR});
	keywords.insert({"copy", TokenType::COPY});
	keywords.insert({"nullptr", TokenType::NUL});
	keywords.insert({"namespace", TokenType::NAMESPACE});
	keywords.insert({"function", TokenType::FX});
	keywords.insert({"if", TokenType::IF});
	keywords.insert({"else", TokenType::ELSE});
	keywords.insert({"for", TokenType::FOR});
	keywords.insert({"while", TokenType::WHILE});
	keywords.insert({"return", TokenType::RETURN});
	keywords.insert({"repeat", TokenType::REPEAT});
	keywords.insert({"struct", TokenType::STRUCT});
	keywords.insert({"asm", TokenType::ASM});

	return LexerNode([keywords](LexerPackage & lexPkg) {
		if(lexPkg.matchAlpha()) {
			while(lexPkg.matchAlpha() || lexPkg.match('_') || lexPkg.matchDigit());
			std::string lexeme = lexPkg.makeLexeme();
			if(keywords.contains(lexeme)) {
				lexPkg.newToken(keywords.at(lexeme));
			}
			else {
				lexPkg.newToken(TokenType::IDENTIFIER);
			}
			return true;
		}
		return false;
	});
}

ltnc::LexerNode ltnc::LexerNodeCreator::string() {
	return LexerNode([](LexerPackage & lexPkg) {
		if(lexPkg.match('"')){
			while(!lexPkg.match('"')) {
				if(lexPkg.match('\\')) {
					bool valid = 
						lexPkg.match('n') ||
						lexPkg.match('\\') ||
						lexPkg.match('t') ||
						lexPkg.match('"');
					if(!valid) {
						lexPkg.error("Invalid escape sequence");
					}
					
				}
				lexPkg.next();
				if(lexPkg.isAtEnd()) {
					lexPkg.error("Unterminated string");
				}
			}
			std::string lexeme = lexPkg.makeLexeme(); 
			lexPkg.newToken(
				TokenType::STRING_LITERAL,
				lexeme.substr(1, lexeme.size()-2));
			return true;
		}
		return false;
	});
}