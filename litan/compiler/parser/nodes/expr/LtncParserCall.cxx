#include "LtncParserCall.hxx"
#include "LtncParserExpr.hxx"
void ltnc::ParserCall::connect(const ParserExpr & expr) {
	this->expr = &expr;
}

std::shared_ptr<ltnc::ExprCall> ltnc::ParserCall::eval(ParserPackage & parsePkg) const {
	if(parsePkg.match(TokenType::IDENTIFIER)) {
		std::string name = parsePkg.prev().string;
		if (parsePkg.match(TokenType::L_PARAN)) {
			std::vector<std::shared_ptr<Expr>> exprs;

			while(!parsePkg.isAtEnd()) {
				if (parsePkg.match(TokenType::R_PARAN)) {
					break;
				}
				auto expr = this->expr->eval(parsePkg);
				exprs.push_back(expr);
				if(parsePkg.match(TokenType::COMMA)) {
					continue;
				}
				else {
					return parsePkg.error("expected ) or , with an expression");
				}
			}

			return std::make_shared<ExprCall>(name, exprs);

			return parsePkg.error("expected )");
		}
		return parsePkg.error("expected (");
	} 
	return parsePkg.error("expected identifier");
}
