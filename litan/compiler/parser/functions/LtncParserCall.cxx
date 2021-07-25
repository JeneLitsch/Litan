#include "LtncParserFunctions.hxx"

std::shared_ptr<std::vector<std::shared_ptr<ltnc::Expr>>> ltnc::parse::parameters(ParserPackage & parsePkg) {
	// parameters
	if (parsePkg.match(TokenType::L_PAREN)) {
		std::vector<std::shared_ptr<Expr>> parameters;
		if (!parsePkg.match(TokenType::R_PAREN)) {
			while(!parsePkg.isAtEnd()) {
				auto expr = expression(parsePkg);
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


std::shared_ptr<ltnc::ExprCall> ltnc::parse::call(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::ARROW)) {
		Namespace ns = nameSpace(parsePkg);
		// function name
		if(parsePkg.match(TokenType::IDENTIFIER)) {
			std::string name = parsePkg.prev().string;
			auto params = parameters(parsePkg);
			return std::make_shared<ExprCall>(name, ns, *params);
		}
	}
	return nullptr;
}