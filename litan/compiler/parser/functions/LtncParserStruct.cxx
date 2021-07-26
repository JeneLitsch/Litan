#include "LtncParserFunctions.hxx"

std::shared_ptr<ltnc::DeclStruct> ltnc::parse::declareStruct(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::STRUCT)) {
		if(parsePkg.match(TokenType::IDENTIFIER)) {
			std::string name = parsePkg.prev().string;
			auto structNode = std::make_shared<DeclStruct>(TypeId(name, parsePkg.ns));
			if(parsePkg.match(TokenType::L_BRACE)) {
				while(auto member = declareVar(parsePkg)) {
					structNode->members.push_back(*member);
				}
				if(parsePkg.match(TokenType::R_BRACE)) {
					return structNode;
				}
				return parsePkg.error("Expected }");
			}
			return parsePkg.error("Expected {");
		}
		return parsePkg.error("Expected struct name");
	}
	return nullptr;
}
