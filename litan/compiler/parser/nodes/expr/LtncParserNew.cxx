#include "LtncParserNew.hxx"
#include "LtncParserExpr.hxx"
#include "LtncParserParameter.hxx"

ltnc::ParserNew::ParserNew(const ParserParameter & exprParam) {
	this->exprParam = &exprParam;
}

std::shared_ptr<ltnc::ExprNew> ltnc::ParserNew::eval(ParserPackage & parsePkg) const {
	if(parsePkg.match(TokenType::NEW)) {
		TypeId typeId = parseType(parsePkg);
		auto parameters = this->exprParam->eval(parsePkg);
		return std::make_shared<ExprNew>(typeId, *parameters);
	}
	return nullptr;
}



