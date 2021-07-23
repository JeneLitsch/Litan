#include "LtncParserParameter.hxx"
#include "LtncParserExpr.hxx"

ltnc::ParserParameter::ParserParameter(const ParserExpr & expr) {
	this->expr = &expr;
}

std::shared_ptr<std::vector<std::shared_ptr<ltnc::Expr>>> ltnc::ParserParameter::eval(ParserPackage & parsePkg) const {
	// parameters
	if (parsePkg.match(TokenType::L_PAREN)) {
		std::vector<std::shared_ptr<Expr>> parameters;
		if (!parsePkg.match(TokenType::R_PAREN)) {
			while(!parsePkg.isAtEnd()) {
				auto expr = this->expr->eval(parsePkg);
				parameters.push_back(expr);
				// next paramter
				if(parsePkg.match(TokenType::COMMA)) {
					continue;
				}
				// end list
				else if (parsePkg.match(TokenType::R_PAREN)) {
					break;
				}
				else {
					return {parsePkg.error("expected ) or , with an expression")};
				}
			}
		}
		return std::make_shared<std::vector<std::shared_ptr<Expr>>>(parameters);
	}
	return {parsePkg.error("expected (")};
}
