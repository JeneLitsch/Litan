#include "LtncParserCall.hxx"
#include "LtncParserExpr.hxx"
#include "LtncParserParameter.hxx"

void ltnc::ParserCall::connect(const ParserParameter & exprParam) {
	this->exprParam = &exprParam;
}

std::shared_ptr<ltnc::ExprCall> ltnc::ParserCall::eval(ParserPackage & parsePkg) const {
	// function name
	if(parsePkg.match(TokenType::IDENTIFIER)) {
		std::string name = parsePkg.prev().string;
		auto parameters = this->exprParam->eval(parsePkg);
		return std::make_shared<ExprCall>(name, *parameters);
		return parsePkg.error("expected (");
	} 
	return parsePkg.error("expected identifier");
}



