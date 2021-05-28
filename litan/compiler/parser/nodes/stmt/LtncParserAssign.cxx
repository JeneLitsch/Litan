#include "LtncParserAssign.hxx"
#include <iostream>

void ltnc::ParserAssign::connect(const ParserNode<Expr> & expr) {
	this->expr = &expr;
}

std::shared_ptr<ltnc::Stmt> ltnc::ParserAssign::eval(ParserPackage & parsePkg) const {
	std::string name = parsePkg.prev().string;
	if (parsePkg.match(TokenType::ASSIGN)) {
		auto expr = this->expr->eval(parsePkg);
		if (parsePkg.match(TokenType::SEMICOLON)) {
			return std::make_shared<StmtAssign>(name, expr);
		}
		return parsePkg.error("assign: expected ;");
	}
	return parsePkg.error("expected =");
}