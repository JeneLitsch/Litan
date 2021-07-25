#include "LtncParserFunctions.hxx"

std::string name(ltnc::ParserPackage & parsePkg) {
	if(parsePkg.match(ltnc::TokenType::IDENTIFIER)) {
		return parsePkg.prev().string;
	}
	parsePkg.error("expected function name");
	return "";
}



std::vector<ltnc::Param> parameterList(ltnc::ParserPackage & parsePkg) {
	// parameter list
	if(parsePkg.match(ltnc::TokenType::L_PAREN)) {
		std::vector<ltnc::Param> parameters;
		while(parsePkg.curr().type == ltnc::TokenType::IDENTIFIER) {
			ltnc::Namespace ns = ltnc::parse::nameSpace(parsePkg);
			if(parsePkg.match(ltnc::TokenType::IDENTIFIER)) {
				ltnc::TypeId typeId = ltnc::TypeId(parsePkg.prev().string, ns);
				// not allowed
				if(typeId == ltnc::TypeId(TVoid)) {
					parsePkg.error("Void is not an allowed paramter type");
				}
				// allowed
				if(parsePkg.match(ltnc::TokenType::IDENTIFIER)) {
					std::string name = parsePkg.prev().string;
					parameters.push_back(ltnc::Param(typeId, name));
				}
				else{
					parsePkg.error("Expected identifier for parameter name");
				}
				if(!parsePkg.match(ltnc::TokenType::COMMA)) {
					break;
				}
			}
			else {
				parsePkg.error("expected Parameter Type");
			}
		}
		if(parsePkg.match(ltnc::TokenType::R_PAREN)) {
			return parameters;
		}
		parsePkg.error("expected )");
	}
	parsePkg.error("expected (");
	return {};
}



ltnc::TypeId returnType(ltnc::ParserPackage & parsePkg) {
	if(parsePkg.match(ltnc::TokenType::ARROW)) {
		return ltnc::parse::type(parsePkg);
	}
	return ltnc::TypeId(TVoid);
}



std::shared_ptr<ltnc::StmtBlock> body(ltnc::ParserPackage & parsePkg) {
	if(auto body = ltnc::parse::codeBlock(parsePkg)) {
		return body;
	}
	return parsePkg.error("expected block statement");
}


bool isInline(ltnc::ParserPackage & parsePkg) {
	return parsePkg.match(ltnc::TokenType::INLINE);
}

std::shared_ptr<ltnc::DeclFunction> ltnc::parse::declareFunction(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::FX)){
		auto name 		= ::name(parsePkg);
		auto parameters = ::parameterList(parsePkg);
		auto returnType = ::returnType(parsePkg);

		bool inlined 	= ::isInline(parsePkg);
		
		auto body 		= ::body(parsePkg);

		return std::make_shared<DeclFunction>(FunctionSignature(returnType, name, parameters, parsePkg.ns), body, inlined);
	}
	return nullptr;
}



