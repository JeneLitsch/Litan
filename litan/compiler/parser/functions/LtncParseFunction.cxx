#include "LtncParserFunctions.hxx"

std::string functionName(ltn::c::ParserPackage & parsePkg) {
	if(parsePkg.match(ltn::c::TokenType::IDENTIFIER)) {
		return parsePkg.prev().string;
	}
	throw ltn::c::error::unnamedFunction(parsePkg);
}


std::optional<ltn::c::Param> parameter(ltn::c::ParserPackage & parsePkg) {
	if(parsePkg.curr().type == ltn::c::TokenType::IDENTIFIER) {
		ltn::c::TypeId typeId = ltn::c::parse::typeId(parsePkg);
		// allowed
		if(parsePkg.match(ltn::c::TokenType::IDENTIFIER)) {
			std::string name = parsePkg.prev().string;
			parsePkg.match(ltn::c::TokenType::COMMA);
			return ltn::c::Param(typeId, name);
		}
		else{
			ltn::c::error::unnamedParameter(parsePkg);
		}
	}
	return {};
}


std::vector<ltn::c::Param> parameterList(ltn::c::ParserPackage & parsePkg) {
	// parameter list
	if(parsePkg.match(ltn::c::TokenType::L_PAREN)) {
		std::vector<ltn::c::Param> parameters;
		while(auto param = parameter(parsePkg)) {
			parameters.push_back(*param);
		}
		if(parsePkg.match(ltn::c::TokenType::R_PAREN)) {
			return parameters;
		}
		throw ltn::c::error::unclosedParameterList(parsePkg);
	}
	throw ltn::c::error::unopenedParameterList(parsePkg);
}



ltn::c::TypeId returnType(ltn::c::ParserPackage & parsePkg) {
	if(parsePkg.match(ltn::c::TokenType::ARROW)) {
		try {
			return ltn::c::parse::typeId(parsePkg);
		}
		catch(...) {}
	}
	throw ltn::c::error::missingReturnType(parsePkg);
}



std::unique_ptr<ltn::c::Stmt> body(ltn::c::ParserPackage & parsePkg) {
	if(auto body = ltn::c::parse::statement(parsePkg)) {
		return body;
	}
	throw ltn::c::error::expectedStatement(parsePkg);
}

bool isTemplate(ltn::c::ParserPackage & parsePkg) {
	return parsePkg.match(ltn::c::TokenType::TEMPLATE);
}

std::optional<std::string> templateParameter(ltn::c::ParserPackage & parsePkg) {
	if(parsePkg.match(ltn::c::TokenType::IDENTIFIER)) {
		std::string name = parsePkg.prev().string;
		parsePkg.match(ltn::c::TokenType::COMMA);
		return name;
	}
	return {};
}

std::vector<std::string> templateParameterList(ltn::c::ParserPackage & parsePkg) {
	if(parsePkg.match(ltn::c::TokenType::SMALLER)) {
		std::vector<std::string> parameters;
		while(auto param = templateParameter(parsePkg)) {
			parameters.push_back(*param);
		}
		if(parsePkg.match(ltn::c::TokenType::BIGGER)) {
			return parameters;
		}
		throw ltn::c::error::unclosedParameterList(parsePkg);
	}
	throw ltn::c::error::unopenedParameterList(parsePkg);
}

std::unique_ptr<ltn::c::DeclFunction> ltn::c::parse::declareFunction(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::FX)){
		auto debugInfo 		= parsePkg.prev().debugInfo; 
		if(isTemplate(parsePkg)) {
			templateParameterList(parsePkg);
			throw ltn::c::Error(ErrorCode::MISC, "Templates are not supported yet", debugInfo);
		}
		else {
			auto name 			= ::functionName(parsePkg);
			auto parameters 	= ::parameterList(parsePkg);
			auto returnType 	= ::returnType(parsePkg);
			auto body 			= ::body(parsePkg);
			auto fxSignature	= FunctionSignature(returnType, name, parameters, parsePkg.ns);
			return std::make_unique<DeclFunction>(
				debugInfo.withFunction(fxSignature),
				fxSignature,
				std::move(body));
		}
	}
	return nullptr;
}



