#include "LtncParserFunctions.hxx"

std::string functionName(ltnc::ParserPackage & parsePkg) {
	if(parsePkg.match(ltnc::TokenType::IDENTIFIER)) {
		return parsePkg.prev().string;
	}
	parsePkg.error("expected function name");
	return "";
}


std::optional<ltnc::Param> parameter(ltnc::ParserPackage & parsePkg) {
	if(parsePkg.curr().type == ltnc::TokenType::IDENTIFIER) {
		ltnc::TypeId typeId = ltnc::parse::typeId(parsePkg);
		// not allowed
		if(typeId == ltnc::TypeId(TVoid)) {
			parsePkg.error("Void is not an allowed parameter type");
		}
		// allowed
		if(parsePkg.match(ltnc::TokenType::IDENTIFIER)) {
			std::string name = parsePkg.prev().string;
			parsePkg.match(ltnc::TokenType::COMMA);
			return ltnc::Param(typeId, name);
		}
		else{
			parsePkg.error("Expected identifier for parameter name");
		}
	}
	return {};
}


std::vector<ltnc::Param> parameterList(ltnc::ParserPackage & parsePkg) {
	// parameter list
	if(parsePkg.match(ltnc::TokenType::L_PAREN)) {
		std::vector<ltnc::Param> parameters;
		while(auto param = parameter(parsePkg)) {
			parameters.push_back(*param);
		}
		if(parsePkg.match(ltnc::TokenType::R_PAREN)) {
			return parameters;
		}
		parsePkg.error("expected ) after parameter list");
	}
	parsePkg.error("expected ( after function name");
	return {};
}



ltnc::TypeId returnType(ltnc::ParserPackage & parsePkg) {
	if(parsePkg.match(ltnc::TokenType::ARROW)) {
		return ltnc::parse::typeId(parsePkg);
	}
	return ltnc::TypeId(TVoid);
}



std::shared_ptr<ltnc::Stmt> body(ltnc::ParserPackage & parsePkg) {
	if(auto body = ltnc::parse::statement(parsePkg)) {
		return body;
	}
	return parsePkg.error("expected block statement");
}


std::shared_ptr<ltnc::DeclFunction> ltnc::parse::declareFunction(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::FX)){
		auto name 		= ::functionName(parsePkg);
		auto parameters = ::parameterList(parsePkg);
		auto returnType = ::returnType(parsePkg);
		auto body 		= ::body(parsePkg);

		return std::make_shared<DeclFunction>(FunctionSignature(returnType, name, parameters, parsePkg.ns), body);
	}
	return nullptr;
}



