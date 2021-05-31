#include "LtncParserFunction.hxx"


void ltnc::ParserFunction::connect(const ParserNode<StmtBlock> & block) {
	
	this->block = &block;
}

std::shared_ptr<ltnc::DeclFunction> ltnc::ParserFunction::eval(ParserPackage & parsePkg) const {
	return this->function(parsePkg);
}


std::shared_ptr<ltnc::DeclFunction> ltnc::ParserFunction::function(ParserPackage & parsePkg) const{
	if(parsePkg.match(TokenType::IDENTIFIER)) {

		std::string name = parsePkg.prev().string;
		if(parsePkg.match(TokenType::L_PARAN)) {

			// parameter list
			std::vector<Param> parameters;
			while(parsePkg.match(TokenType::IDENTIFIER)) {
				Type type = Type(parsePkg.prev().string);
				if(type == "voi") {
					return parsePkg.error("Void is not an allowed paramter type");
				}
				if(parsePkg.match(TokenType::IDENTIFIER)) {
					std::string name = parsePkg.prev().string;
					parameters.push_back(Param(type, name));
				}
				else{
					return parsePkg.error("Expected identifier for parameter name");
				}
				if(!parsePkg.match(TokenType::COMMA)) {
					break;
				}
			}
			if(parsePkg.match(TokenType::R_PARAN)) {
				if(parsePkg.match(TokenType::IDENTIFIER)) {
					Type returnType = Type(parsePkg.prev().string);
					if(auto body = this->block->eval(parsePkg)) {
						return std::make_shared<DeclFunction>(FxSignature(returnType, name, parameters), body);
					}					
				}
				else {
					return parsePkg.error("Missing or invalid return type");
				}

				// function body
				return parsePkg.error("expected block statement");
			}
			return parsePkg.error("expected )");
		}
		return parsePkg.error("expected (");
	}
	return parsePkg.error("expected identifier");
}
