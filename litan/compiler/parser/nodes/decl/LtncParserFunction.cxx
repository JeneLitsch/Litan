#include "LtncParserFunction.hxx"


void ltnc::ParserFunction::connect(const ParserNode<StmtBlock> & block) {
	this->block = &block;
}



std::shared_ptr<ltnc::DeclFunction> ltnc::ParserFunction::eval(ParserPackage & parsePkg) const {
	auto name 		= this->name(parsePkg);
	auto parameters = this->parameterList(parsePkg);
	auto returnType = this->returnType(parsePkg);
	auto body 		= this->body(parsePkg);

	return std::make_shared<DeclFunction>(FxSignature(returnType, name, parameters), body);
}



std::string ltnc::ParserFunction::name(ParserPackage & parsePkg) const {
	if(parsePkg.match(TokenType::IDENTIFIER)) {
		return parsePkg.prev().string;
	}
	parsePkg.error("expected function name");
	return "";
}



std::vector<ltnc::Param> ltnc::ParserFunction::parameterList(ParserPackage & parsePkg) const {
	// parameter list
	if(parsePkg.match(TokenType::L_PARAN)) {
		std::vector<Param> parameters;
		while(parsePkg.match(TokenType::IDENTIFIER)) {
			Type type = Type(parsePkg.prev().string);
			// not allowed
			if(type == "voi") {
				parsePkg.error("Void is not an allowed paramter type");
			}
			// allowed
			if(parsePkg.match(TokenType::IDENTIFIER)) {
				std::string name = parsePkg.prev().string;
				parameters.push_back(Param(type, name));
			}
			else{
				parsePkg.error("Expected identifier for parameter name");
			}
			if(!parsePkg.match(TokenType::COMMA)) {
				break;
			}
		}
		if(parsePkg.match(TokenType::R_PARAN)) {
			return parameters;
		}
		parsePkg.error("expected )");
	}
	parsePkg.error("expected (");
	return {};
}



ltnc::Type ltnc::ParserFunction::returnType(ParserPackage & parsePkg) const {
	if(parsePkg.match(TokenType::IDENTIFIER)) {
		return Type(parsePkg.prev().string);
	}
	parsePkg.error("Missing return type");
	return Type("ERROR");
}



std::shared_ptr<ltnc::StmtBlock> ltnc::ParserFunction::body(ParserPackage & parsePkg) const {
	if(auto body = this->block->eval(parsePkg)) {
		return body;
	}
	return parsePkg.error("expected block statement");
}


