#include "LtncParserCall.hxx"
#include "LtncParserExpr.hxx"
#include "LtncParserParameter.hxx"

ltnc::ParserCall::ParserCall(const ParserParameter & exprParam) {
	this->exprParam = &exprParam;
}

std::shared_ptr<ltnc::ExprCall> ltnc::ParserCall::eval(ParserPackage & parsePkg) const {
	if(parsePkg.match(TokenType::ARROW)) {
		Namespace ns = parserNamespace(parsePkg);
		// function name
		if(parsePkg.match(TokenType::IDENTIFIER)) {
			std::string name = parsePkg.prev().string;
			std::cout << ns << name << std::endl; 
			auto parameters = this->exprParam->eval(parsePkg);
			return std::make_shared<ExprCall>(name, ns, *parameters);
		}
	}
	return nullptr;
}



