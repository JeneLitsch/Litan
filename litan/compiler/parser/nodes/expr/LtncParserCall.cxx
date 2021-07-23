#include "LtncParserCall.hxx"
#include "LtncParserExpr.hxx"
#include "LtncParserParameter.hxx"

ltnc::ParserCall::ParserCall(const ParserParameter & exprParam) {
	this->exprParam = &exprParam;
}

std::shared_ptr<ltnc::ExprCall> ltnc::ParserCall::eval(ParserPackage & parsePkg) const {
	if(parsePkg.match(TokenType::ARROW)) {
		// function name
		if(parsePkg.match(TokenType::IDENTIFIER)) {
			std::string name = parsePkg.prev().string;
			auto parameters = this->exprParam->eval(parsePkg);
			return std::make_shared<ExprCall>(name, *parameters);
		}
	}
	return nullptr;
}



