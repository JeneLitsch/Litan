#include "LtncParserDeclVar.hxx"

std::shared_ptr<ltnc::DeclVar> ltnc::ParserDeclVar::eval(ParserPackage & parsePkg) const {
	if(parsePkg.match(TokenType::VAR)) {
		if(parsePkg.match(TokenType::IDENTIFIER)) {
			std::string typeName = parsePkg.prev().string;
			if(parsePkg.match(TokenType::IDENTIFIER)) {
				std::string name = parsePkg.prev().string;
				if (parsePkg.match(TokenType::SEMICOLON)) {
					return std::make_shared<DeclVar>(name, TypeId(typeName));
				}
				return parsePkg.error("expected ;");
			}
			return parsePkg.error("expected identifier");
		}
		return parsePkg.error("expected typeName");
	}
	return nullptr;
}
