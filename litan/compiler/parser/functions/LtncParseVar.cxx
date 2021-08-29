#include "LtncParserFunctions.hxx"


std::unique_ptr<ltn::c::ExprVar> ltn::c::parse::var(ParserPackage & parsePkg) {
	// variables and constants
	if (parsePkg.match(TokenType::IDENTIFIER)) {
		const DebugInfo & debugInfo = parsePkg.prev().debugInfo;
		
		const std::string varName = parsePkg.prev().string;
		auto exprVar = std::make_unique<ExprVar>(debugInfo, varName);
		auto * last = exprVar.get();

		
		while(parsePkg.match(TokenType::DOT)) {
			if (!parsePkg.match(TokenType::IDENTIFIER)) {
				throw ltn::c::error::unnamedVariable(parsePkg);
			}
			const std::string varName = parsePkg.prev().string;
			auto && next = std::make_unique<ExprVar>(debugInfo, varName);
			last->next = std::move(next);
			last = last->next.get();
		}
		return exprVar;
	}
	return nullptr;
}

ltn::c::VarId parseVarName(ltn::c::ParserPackage & parsePkg) {
	if(parsePkg.match(ltn::c::TokenType::IDENTIFIER)) {
		return ltn::c::VarId(parsePkg.prev().string);
	}
	throw ltn::c::error::unnamedVariable(parsePkg);
}


std::unique_ptr<ltn::c::StmtAssign> parseAssign(
	const ltn::c::VarId & varId,
	ltn::c::ParserPackage & parsePkg) {
	if(parsePkg.match(ltn::c::TokenType::ASSIGN)) {
		const ltn::c::DebugInfo & debugInfo = parsePkg.prev().debugInfo;
		auto expr = ltn::c::parse::expression(parsePkg);
		auto access = std::make_unique<ltn::c::ExprVar>(debugInfo, varId);
		return std::make_unique<ltn::c::StmtAssign>(debugInfo, std::move(access), std::move(expr));
	}
	return nullptr;
}


std::unique_ptr<ltn::c::StmtVar> ltn::c::parse::declareVar(ParserPackage & parsePkg)  {
	if(parsePkg.match(TokenType::VAR)) {
		auto debugInfo = parsePkg.prev().debugInfo;
		auto typeId = parse::typeId(parsePkg);
		auto varId = parseVarName(parsePkg);
		auto assign = parseAssign(varId, parsePkg);
		if (parsePkg.match(TokenType::SEMICOLON)) {
			return std::make_unique<StmtVar>(debugInfo, varId, typeId, std::move(assign));
		}
		throw error::expectedSemicolon(parsePkg);
	}
	return nullptr;
}

