#include "LtncParserPrint.hxx"


void ltnc::ParserPrint::connect(const ParserNode<Expr> & expr) {
	this->expr = &expr;
}

std::shared_ptr<ltnc::Stmt> ltnc::ParserPrint::eval(ParserPackage & parsePkg) const {
	if(parsePkg.match(TokenType::PRINT)) {
		auto expr = this->expr->eval(parsePkg);
		if (parsePkg.match(TokenType::SEMICOLON)) {
			return std::make_shared<StmtPrint>(expr);
		}
		return parsePkg.error("expected ;");
	}
	return nullptr;
}
