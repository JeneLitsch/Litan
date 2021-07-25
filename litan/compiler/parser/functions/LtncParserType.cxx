#include "LtncParserFunctions.hxx"

std::shared_ptr<ltnc::Type> ltnc::parse::declareType(ParserPackage & parsePkg) {
	if (parsePkg.match(TokenType::TYPEDEF)) {
		if(parsePkg.match(TokenType::IDENTIFIER)){
			std::string typeName = parsePkg.prev().string;
			if(parsePkg.match(TokenType::SEMICOLON)){
				return std::make_shared<Type>(TypeId(typeName, parsePkg.ns));
			}
			parsePkg.error("expected ;");
		}
		parsePkg.error("expected typename");
	}
	return nullptr;
}
