#include "LtncParserDel.hxx"
#include "LtncParserExpr.hxx"


ltnc::ParserDel::ParserDel(const ParserNode<ExprVar> & exprVar) {
	this->exprVar = &exprVar;
}


std::shared_ptr<ltnc::ExprDel> ltnc::ParserDel::eval(ParserPackage & parsePkg) const {
	if(parsePkg.match(TokenType::DEL)) {
		if(auto var = this->exprVar->eval(parsePkg)) {
			return std::make_shared<ExprDel>(var);
		}
		throw std::runtime_error("Expected variable name");
	}
	return nullptr;
}



