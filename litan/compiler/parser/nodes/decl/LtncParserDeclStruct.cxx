#include "LtncParserDeclStruct.hxx"

void ltnc::ParserDeclStruct::connect(const ParserNode<DeclVar> & declVar) {
	this->declVar = &declVar;
}

std::shared_ptr<ltnc::DeclStruct> ltnc::ParserDeclStruct::eval(ParserPackage & parsePkg) const {
	if(parsePkg.match(TokenType::STRUCT)) {
		if(parsePkg.match(TokenType::IDENTIFIER)) {
			std::string name = parsePkg.prev().string;
			auto structNode = std::make_shared<DeclStruct>(name);
			if(!parsePkg.match(TokenType::L_BRACE)) {
				return parsePkg.error("Expected {");
			}
			while(auto member = declVar->eval(parsePkg)) {
				structNode->members.push_back(member);
			}
			if(!parsePkg.match(TokenType::R_BRACE)) {
				return parsePkg.error("Expected }");
			}
			parsePkg.match(TokenType::SEMICOLON);
			return structNode;
		}
		return parsePkg.error("Expected struct name");
	}
	return nullptr;
}
