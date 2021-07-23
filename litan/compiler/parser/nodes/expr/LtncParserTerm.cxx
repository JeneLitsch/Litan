#include "LtncParserTerm.hxx"

ltnc::ParserTerm::ParserTerm(const ParserNode<Expr> & product) {
	this->product = &product;
}

std::shared_ptr<ltnc::Expr> ltnc::ParserTerm::eval(ParserPackage & parsePkg) const {
	std::shared_ptr<ltnc::Expr> l = this->product->eval(parsePkg);
	while(parsePkg.match({TokenType::PLUS, TokenType::MINUS})) {
		Token op = parsePkg.prev();
		std::shared_ptr<ltnc::Expr> r = this->product->eval(parsePkg);
		l = std::make_shared<ExprBinary>(op.type, l, r);
	}
	return l;
}
