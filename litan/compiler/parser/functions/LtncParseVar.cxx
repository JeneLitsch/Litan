#include "LtncParserFunctions.hxx"


std::shared_ptr<ltnc::ExprVar> ltnc::parse::var(ParserPackage & parsePkg) {
	// variables and constants
	if (parsePkg.match(TokenType::IDENTIFIER)) {
		const DebugInfo & debugInfo = parsePkg.prev().debugInfo;
		auto exprVar = std::make_shared<ExprVar>(debugInfo, parsePkg.prev().string);
		while(parsePkg.match(TokenType::DOT)) {
			if (!parsePkg.match(TokenType::IDENTIFIER)) {
				throw ltnc::error::unnamedVariable(parsePkg);
			}
			exprVar->path.push_back(parsePkg.prev().string);
		}
		return exprVar;
	}
	return nullptr;
}

ltnc::VarId parseVarName(ltnc::ParserPackage & parsePkg) {
	if(parsePkg.match(ltnc::TokenType::IDENTIFIER)) {
		return ltnc::VarId(parsePkg.prev().string);
	}
	throw ltnc::error::unnamedVariable(parsePkg);
}


std::shared_ptr<ltnc::StmtAssign> parseAssign(
	const ltnc::VarId & varId,
	ltnc::ParserPackage & parsePkg) {
	if(parsePkg.match(ltnc::TokenType::ASSIGN)) {
		const ltnc::DebugInfo & debugInfo = parsePkg.prev().debugInfo;
		auto expr = ltnc::parse::expression(parsePkg);
		auto access = std::make_shared<ltnc::ExprVar>(debugInfo, varId);
		return std::make_shared<ltnc::StmtAssign>(debugInfo, access, expr);
	}
	return nullptr;
}


std::shared_ptr<ltnc::StmtVar> ltnc::parse::declareVar(ParserPackage & parsePkg)  {
	if(parsePkg.match(TokenType::VAR)) {
		auto debugInfo = parsePkg.prev().debugInfo;
		auto typeId = parse::typeId(parsePkg);
		auto varId = parseVarName(parsePkg);
		auto assign = parseAssign(varId, parsePkg);
		if (parsePkg.match(TokenType::SEMICOLON)) {
			return std::make_shared<StmtVar>(debugInfo, varId, typeId, assign);
		}
		throw error::expectedSemicolon(parsePkg);
	}
	return nullptr;
}

