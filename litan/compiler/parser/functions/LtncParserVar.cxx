#include "LtncParserFunctions.hxx"

std::shared_ptr<ltnc::ExprVar> ltnc::parse::var(ParserPackage & parsePkg) {
	// variables and constants
	if (parsePkg.match(TokenType::IDENTIFIER)) {
		auto exprVar = std::make_shared<ExprVar>(parsePkg.prev().string);
		while(parsePkg.match(TokenType::DOT)) {
			if (!parsePkg.match(TokenType::IDENTIFIER)) {
				return parsePkg.error("expected identifier after .");
			}
			exprVar->path.push_back(parsePkg.prev().string);
		}
		return exprVar;
	}
	return nullptr;
}

std::shared_ptr<ltnc::DeclVar> ltnc::parse::declareVar(ParserPackage & parsePkg)  {
	if(parsePkg.match({TokenType::VAR, TokenType::CONST})) {
		TypeId typeId = type(parsePkg);
		if(typeId.name == TVoid) {
			return parsePkg.error("Void is not allowed as variable type");
		}
		if(parsePkg.match(TokenType::IDENTIFIER)) {
			std::string name = parsePkg.prev().string;
			// direct initialisation
			std::shared_ptr<StmtAssign> assign = nullptr;
			if(parsePkg.match(TokenType::ASSIGN)) {
				auto expr = expression(parsePkg);
				auto access = std::make_shared<ExprVar>(name);
				assign = std::make_shared<StmtAssign>(
					access,
					expr);
			}
			if (parsePkg.match(TokenType::SEMICOLON)) {
				return std::make_shared<DeclVar>(name, typeId, assign);
			}
			return parsePkg.error("expected ;");
		}
	}
	return nullptr;
}
