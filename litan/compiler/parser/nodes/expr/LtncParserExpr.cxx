#include "LtncParserExpr.hxx"

void ltnc::ParserExpr::connect(
	const ParserNode<Expr> & comparison,
	const ParserNode<ExprNew> & newstruct,
	const ParserNode<ExprDel> & delstruct) {
	this->comparison = &comparison;
	this->newstruct = &newstruct;
	this->delstruct = &delstruct;
}

std::shared_ptr<ltnc::Expr> ltnc::ParserExpr::eval(ParserPackage & parsePkg) const {
	if(auto expr = this->newstruct->eval(parsePkg)) {
		return expr;
	}
	if(auto expr = this->delstruct->eval(parsePkg)) {
		return expr;
	}
	return this->comparison->eval(parsePkg);
}
