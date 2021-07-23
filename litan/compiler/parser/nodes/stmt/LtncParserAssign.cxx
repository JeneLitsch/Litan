#include "LtncParserAssign.hxx"
#include <iostream>

ltnc::ParserAssign::ParserAssign(
	const ParserNode<Expr> & expr,
	const ParserNode<ExprVar> & var) {
	
	this->expr = &expr;
	this->var = &var;
}

std::shared_ptr<ltnc::Stmt> ltnc::ParserAssign::eval(ParserPackage & parsePkg) const {
	if(auto exprVar = this->var->eval(parsePkg)) {
		if (parsePkg.match(TokenType::ASSIGN)) {
			auto expr = this->expr->eval(parsePkg);
			if (parsePkg.match(TokenType::SEMICOLON)) {
				return std::make_shared<StmtAssign>(exprVar, expr);
			}
			return parsePkg.error("assign: expected ;");
		}
		return parsePkg.error("expected =");
	}
	return nullptr;
}