#include "LtncParserProduct.hxx"

void ltnc::ParserProduct::connect(const ParserNode<Expr> & primary) {
	this->primary = &primary;
}

std::shared_ptr<ltnc::Expr> ltnc::ParserProduct::eval(ParserPackage & parsePkg) const {
	std::shared_ptr<ltnc::Expr> l = primary->eval(parsePkg);
	while(parsePkg.match({TokenType::STAR, TokenType::SLASH, TokenType::MOD})) {
		Token op = parsePkg.prev();
		std::shared_ptr<ltnc::Expr> r = primary->eval(parsePkg);
		l = std::make_shared<ExprBinary>(op.type, l, r);
	}
	return l;
}
