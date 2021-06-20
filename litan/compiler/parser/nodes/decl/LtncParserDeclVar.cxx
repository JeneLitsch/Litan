#include "LtncParserDeclVar.hxx"

void ltnc::ParserDeclVar::connect(const ParserNode<Expr> & expr) {
	this->expr = &expr;
}


std::shared_ptr<ltnc::DeclVar> ltnc::ParserDeclVar::eval(ParserPackage & parsePkg) const {
	if(parsePkg.match({TokenType::VAR, TokenType::CONST})) {
		bool constant = parsePkg.prev().type == TokenType::CONST;
		if(parsePkg.match(TokenType::IDENTIFIER)) {
			std::string typeName = parsePkg.prev().string;
			if(parsePkg.match(TokenType::IDENTIFIER)) {
				std::string name = parsePkg.prev().string;
				// direct initialisation
				std::shared_ptr<StmtAssign> assign = nullptr;
				if(parsePkg.match(TokenType::ASSIGN)) {
					auto expr = this->expr->eval(parsePkg);
					auto access = std::make_shared<ExprVar>(name);
					assign = std::make_shared<StmtAssign>(
						access,
						expr);
				}
				if(constant && !assign) {
					return parsePkg.error("Unassigned const value");
				}
				if (parsePkg.match(TokenType::SEMICOLON)) {
					return std::make_shared<DeclVar>(name, TypeId(typeName), assign);
				}
				return parsePkg.error("expected ;");
			}
			return parsePkg.error("expected identifier");
		}
		return parsePkg.error("expected typeName");
	}
	return nullptr;
}
