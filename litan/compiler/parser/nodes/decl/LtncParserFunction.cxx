#include "LtncParserFunction.hxx"
#include "LtncBaseTypes.hxx"

ltnc::ParserFunction::ParserFunction(const ParserNode<StmtBlock> & block) {
	this->block = &block;
}



std::shared_ptr<ltnc::DeclFunction> ltnc::ParserFunction::eval(ParserPackage & parsePkg) const {
	if(parsePkg.match(TokenType::FX)){
		auto name 		= this->name(parsePkg);
		auto parameters = this->parameterList(parsePkg);
		auto returnType = this->returnType(parsePkg);

		bool inlined 	= this->isInline(parsePkg);
		
		auto body 		= this->body(parsePkg);

		return std::make_shared<DeclFunction>(FunctionSignature(returnType, name, parameters, parsePkg.ns), body, inlined);
	}
	return nullptr;
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
	if(parsePkg.match(TokenType::L_PAREN)) {
		std::vector<Param> parameters;
		while(parsePkg.curr().type == TokenType::IDENTIFIER) {
			Namespace ns = parserNamespace(parsePkg);
			if(parsePkg.match(TokenType::IDENTIFIER)) {
				TypeId typeId = TypeId(parsePkg.prev().string, ns);
				// not allowed
				if(typeId == TypeId(TVoid)) {
					parsePkg.error("Void is not an allowed paramter type");
				}
				// allowed
				if(parsePkg.match(TokenType::IDENTIFIER)) {
					std::string name = parsePkg.prev().string;
					parameters.push_back(Param(typeId, name));
				}
				else{
					parsePkg.error("Expected identifier for parameter name");
				}
				if(!parsePkg.match(TokenType::COMMA)) {
					break;
				}
			}
			else {
				parsePkg.error("expected Parameter Type");
			}
		}
		if(parsePkg.match(TokenType::R_PAREN)) {
			return parameters;
		}
		parsePkg.error("expected )");
	}
	parsePkg.error("expected (");
	return {};
}



ltnc::TypeId ltnc::ParserFunction::returnType(ParserPackage & parsePkg) const {
	if(parsePkg.match(TokenType::ARROW)) {
		return parseType(parsePkg);
	}
	return TypeId(TVoid);
}



std::shared_ptr<ltnc::StmtBlock> ltnc::ParserFunction::body(ParserPackage & parsePkg) const {
	if(auto body = this->block->eval(parsePkg)) {
		return body;
	}
	return parsePkg.error("expected block statement");
}


bool ltnc::ParserFunction::isInline(ParserPackage & parsePkg) const {
	return parsePkg.match(TokenType::INLINE);
}
