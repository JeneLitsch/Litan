#include "LtncParserDeclVar.hxx"
#include "LtncBaseTypes.hxx"

ltnc::ParserDeclVar::ParserDeclVar(const ParserNode<Expr> & expr) {
	this->expr = &expr;
}


std::shared_ptr<ltnc::DeclVar> ltnc::ParserDeclVar::eval(ParserPackage & parsePkg) const {
	if(parsePkg.match({TokenType::VAR, TokenType::CONST})) {
		TypeId typeId = parseType(parsePkg);
		if(typeId.name == TVoid) {
			return parsePkg.error("Void is not allowed as variable type");
		}
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
			if (parsePkg.match(TokenType::SEMICOLON)) {
				return std::make_shared<DeclVar>(name, typeId, assign);
			}
			return parsePkg.error("expected ;");
		}
	}
	return nullptr;
}
