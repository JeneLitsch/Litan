#include "LtncParserExpr.hxx"

ltnc::ParserExpr::ParserExpr(
	const ParserNode<Expr> & comparison)
	: comparison(comparison) {}

std::shared_ptr<ltnc::Expr> ltnc::ParserExpr::eval(ParserPackage & parsePkg) const {
	return this->comparison.eval(parsePkg);
}
