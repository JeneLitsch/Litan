#include "LtncParserFunctions.hxx"

std::string functionName(ltnc::ParserPackage & parsePkg) {
	if(parsePkg.match(ltnc::TokenType::IDENTIFIER)) {
		return parsePkg.prev().string;
	}
	throw ltnc::error::unnamedFunction(parsePkg);
}


std::optional<ltnc::Param> parameter(ltnc::ParserPackage & parsePkg) {
	if(parsePkg.curr().type == ltnc::TokenType::IDENTIFIER) {
		ltnc::TypeId typeId = ltnc::parse::typeId(parsePkg);
		// allowed
		if(parsePkg.match(ltnc::TokenType::IDENTIFIER)) {
			std::string name = parsePkg.prev().string;
			parsePkg.match(ltnc::TokenType::COMMA);
			return ltnc::Param(typeId, name);
		}
		else{
			ltnc::error::unnamedParameter(parsePkg);
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
		throw ltnc::error::unclosedParameterList(parsePkg);
	}
	throw ltnc::error::unopenedParameterList(parsePkg);
}



ltnc::TypeId returnType(ltnc::ParserPackage & parsePkg) {
	if(parsePkg.match(ltnc::TokenType::ARROW)) {
		try {
			return ltnc::parse::typeId(parsePkg);
		}
		catch(...) {}
	}
	throw ltnc::error::missingReturnType(parsePkg);
}



std::shared_ptr<ltnc::Stmt> body(ltnc::ParserPackage & parsePkg) {
	if(auto body = ltnc::parse::statement(parsePkg)) {
		return body;
	}
	throw ltnc::error::expectedStatement(parsePkg);
}

bool isTemplate(ltnc::ParserPackage & parsePkg) {
	return parsePkg.match(ltnc::TokenType::TEMPLATE);
}

std::optional<std::string> templateParameter(ltnc::ParserPackage & parsePkg) {
	if(parsePkg.match(ltnc::TokenType::IDENTIFIER)) {
		std::string name = parsePkg.prev().string;
		parsePkg.match(ltnc::TokenType::COMMA);
		return name;
	}
	return {};
}

std::vector<std::string> templateParameterList(ltnc::ParserPackage & parsePkg) {
	if(parsePkg.match(ltnc::TokenType::SMALLER)) {
		std::vector<std::string> parameters;
		while(auto param = templateParameter(parsePkg)) {
			parameters.push_back(*param);
		}
		if(parsePkg.match(ltnc::TokenType::BIGGER)) {
			return parameters;
		}
		throw ltnc::error::unclosedParameterList(parsePkg);
	}
	throw ltnc::error::unopenedParameterList(parsePkg);
}

std::shared_ptr<ltnc::DeclFunction> ltnc::parse::declareFunction(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::FX)){
		auto debugInfo 		= parsePkg.prev().debugInfo; 
		if(isTemplate(parsePkg)) {
			templateParameterList(parsePkg);
			throw ltnc::Error(ErrorCode::MISC, "Templates are not supported yet", debugInfo);
		}
		else {
			auto name 			= ::functionName(parsePkg);
			auto parameters 	= ::parameterList(parsePkg);
			auto returnType 	= ::returnType(parsePkg);
			auto body 			= ::body(parsePkg);
			auto fxSignature	= FunctionSignature(returnType, name, parameters, parsePkg.ns);
			return std::make_shared<DeclFunction>(debugInfo.withFunction(fxSignature), fxSignature, body);
		}
	}
	return nullptr;
}



