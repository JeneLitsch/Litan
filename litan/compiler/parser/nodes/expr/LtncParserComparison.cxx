#include "LtncParserComparison.hxx"

void ltnc::ParserComparison::connect(const ParserNode<Expr> & term) {
	this->term = &term;
}

std::shared_ptr<ltnc::Expr> ltnc::ParserComparison::eval(ParserPackage & parsePkg) const {
	std::shared_ptr<ltnc::Expr> l = this->term->eval(parsePkg);
	while(parsePkg.match({
		TokenType::EQUAL,
		TokenType::UNEQUAL,
		TokenType::BIGGER,
		TokenType::BIGGEREQUAL,
		TokenType::SMALLER,
		TokenType::SMALLEREQUAL})) {
		
		Token op = parsePkg.prev();
		std::shared_ptr<ltnc::Expr> r = this->term->eval(parsePkg);
		l = std::make_shared<ExprBinary>(op.type, l, r);
	}
	return l;
}
