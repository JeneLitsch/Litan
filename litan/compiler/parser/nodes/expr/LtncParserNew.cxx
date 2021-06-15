#include "LtncParserNew.hxx"
#include "LtncParserExpr.hxx"
#include "LtncParserParameter.hxx"

void ltnc::ParserNew::connect(const ParserParameter & exprParam) {
	this->exprParam = &exprParam;
}

std::shared_ptr<ltnc::ExprNew> ltnc::ParserNew::eval(ParserPackage & parsePkg) const {
	if(parsePkg.match(TokenType::NEW)) {
		if(parsePkg.match(TokenType::IDENTIFIER)) {
			std::string typeName = parsePkg.prev().string;
			auto parameters = this->exprParam->eval(parsePkg);
			return std::make_shared<ExprNew>(typeName, *parameters);
		}
		return parsePkg.error("expected type tame after \"new\"");
	}
	return nullptr;
}



