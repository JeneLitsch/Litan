#include "LtncParserCall.hxx"
#include "LtncParserExpr.hxx"



void ltnc::ParserCall::connect(const ParserExpr & expr) {
	this->expr = &expr;
}



std::shared_ptr<ltnc::ExprCall> ltnc::ParserCall::eval(ParserPackage & parsePkg) const {
	// function name
	if(parsePkg.match(TokenType::IDENTIFIER)) {
		std::string name = parsePkg.prev().string;
		if (parsePkg.match(TokenType::L_PAREN)) {
			auto parameters = this->evalParameters(parsePkg);
			return std::make_shared<ExprCall>(name, parameters);
		}
		return parsePkg.error("expected (");
	} 
	return parsePkg.error("expected identifier");
}



std::vector<std::shared_ptr<ltnc::Expr>> ltnc::ParserCall::evalParameters(ParserPackage & parsePkg) const {
	// parameters
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
	return parameters;
}
