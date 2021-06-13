#include "LtncParserProduct.hxx"

void ltnc::ParserProduct::connect(const ParserNode<Expr> & unary) {
	this->unary = &unary;
}

std::shared_ptr<ltnc::Expr> ltnc::ParserProduct::eval(ParserPackage & parsePkg) const {
	std::shared_ptr<ltnc::Expr> l = unary->eval(parsePkg);
	while(parsePkg.match({TokenType::STAR, TokenType::SLASH, TokenType::MOD})) {
		Token op = parsePkg.prev();
		std::shared_ptr<ltnc::Expr> r = unary->eval(parsePkg);
		l = std::make_shared<ExprBinary>(op.type, l, r);
	}
	return l;
}
