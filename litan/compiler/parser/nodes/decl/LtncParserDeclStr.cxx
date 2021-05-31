#include "LtncParserDeclStr.hxx"

std::shared_ptr<ltnc::DeclVar> ltnc::ParserDeclStr::eval(ParserPackage & parsePkg) const {
	if(parsePkg.match(TokenType::STR)) {
		if(parsePkg.match(TokenType::IDENTIFIER)){
			std::string name = parsePkg.prev().string;
			if (parsePkg.match(TokenType::SEMICOLON)) {
				return std::make_shared<DeclVar>(name, Type::STR);
			}
			return parsePkg.error("expected ;");
		}
		return parsePkg.error("expected identifier");
	}
	return nullptr;
}
