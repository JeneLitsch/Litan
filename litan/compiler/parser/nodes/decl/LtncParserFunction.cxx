#include "LtncParserFunction.hxx"


void ltnc::ParserFunction::connect(const ParserNode<StmtBlock> & block) {
	
	this->block = &block;
}

std::shared_ptr<ltnc::DeclFunction> ltnc::ParserFunction::eval(ParserPackage & parsePkg) const {
	return this->function(parsePkg);
}

ltnc::Type ltnc::ParserFunction::toType(TokenType tokenType) const {
	switch (tokenType)
	{
	case TokenType::VOI: return Type::VOI;
	case TokenType::INT: return Type::INT;
	case TokenType::FLT: return Type::FLT;
	case TokenType::ARR: return Type::ARR;
	case TokenType::STR: return Type::STR;
	default:break;
	}
}

std::shared_ptr<ltnc::DeclFunction> ltnc::ParserFunction::function(ParserPackage & parsePkg) const{
	if(parsePkg.match(TokenType::IDENTIFIER)) {

		std::string name = parsePkg.prev().string;
		if(parsePkg.match(TokenType::L_PARAN)) {

			// parameter list
			std::vector<Param> parameters;
			while(parsePkg.match({
				TokenType::VOI,
				TokenType::INT,
				TokenType::ARR,
				TokenType::STR,
				TokenType::FLT})) {
				TokenType tokenType = parsePkg.prev().type;
				Type type = this->toType(tokenType);
				if(tokenType == TokenType::VOI) {
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
				
				//return type
				Type returnType;
				if(parsePkg.match(TokenType::VOI)) {
					returnType = Type(Type::VOI);
				}
				else if(parsePkg.match(TokenType::INT)) {
					returnType = Type::INT;
				}
				else if(parsePkg.match(TokenType::FLT)) {
					returnType = Type::FLT;
				}
				else if(parsePkg.match(TokenType::ARR)) {
					returnType = Type::ARR;
				}
				else if(parsePkg.match(TokenType::STR)) {
					returnType = Type::STR;
				}
				else {
					return parsePkg.error("Missing or invalid return type");
				}

				// function body
				if(auto body = this->block->eval(parsePkg)) {
					return std::make_shared<DeclFunction>(FxSignature(returnType, name, parameters), body);
				}
				return parsePkg.error("expected block statement");
			}
			return parsePkg.error("expected )");
		}
		return parsePkg.error("expected (");
	}
	return parsePkg.error("expected identifier");
}
