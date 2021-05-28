#include "LtncParserExpr.hxx"

void ltnc::ParserExpr::connect(const ParserNode<Expr> & comparison) {
	this->comparison = &comparison;
}

std::shared_ptr<ltnc::Expr> ltnc::ParserExpr::eval(ParserPackage & parsePkg) const {
	return this->comparison->eval(parsePkg);
}
