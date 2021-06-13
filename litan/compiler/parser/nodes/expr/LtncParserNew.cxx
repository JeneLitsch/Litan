#include "LtncParserNew.hxx"
#include "LtncParserExpr.hxx"


std::shared_ptr<ltnc::ExprNew> ltnc::ParserNew::eval(ParserPackage & parsePkg) const {
	if(parsePkg.match(TokenType::NEW)) {
		if(parsePkg.match(TokenType::IDENTIFIER)) {
			std::string typeName = parsePkg.prev().string;
			if(!parsePkg.match(TokenType::L_PAREN)) {
				parsePkg.error("expected {");
			}
			if(!parsePkg.match(TokenType::R_PAREN)) {
				parsePkg.error("expected }");
			}
			return std::make_shared<ExprNew>(typeName);
		}
		return parsePkg.error("expected type tame after \"new\"");
	}
	return nullptr;
}



