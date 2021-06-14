#include "LtncParserUnary.hxx"
#include <iostream>
void ltnc::ParserUnary::connect(
	const ParserNode<Expr> & primary) {
	
	this->primary = &primary;
}

std::shared_ptr<ltnc::Expr> ltnc::ParserUnary::eval(ParserPackage & parsePkg) const  {
	if(parsePkg.match({
		TokenType::MINUS,
		TokenType::LOG_NOT,
		TokenType::BIT_NOT})) {
		Token op = parsePkg.prev();
		std::shared_ptr<ltnc::Expr> r = this->eval(parsePkg);
		return std::make_shared<ExprUnary>(op.type, r);
	}
	return this->primary->eval(parsePkg);	
}
