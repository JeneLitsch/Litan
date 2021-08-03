#include "LtncParserFunctions.hxx"

auto parameters(ltnc::ParserPackage & parsePkg) {
	// parameters
	if (parsePkg.match(ltnc::TokenType::L_PAREN)) {
		std::vector<std::shared_ptr<ltnc::Expr>> parameters;
		if (!parsePkg.match(ltnc::TokenType::R_PAREN)) {
			while(!parsePkg.isAtEnd()) {
				auto expr = ltnc::parse::expression(parsePkg);
				parameters.push_back(expr);
				// next paramter
				if(parsePkg.match(ltnc::TokenType::COMMA)) {
					continue;
				}
				// end list
				else if (parsePkg.match(ltnc::TokenType::R_PAREN)) {
					break;
				}
				else {
					throw ltnc::error::unclosedParameterList(parsePkg);
				}
			}
		}
		return std::vector<std::shared_ptr<ltnc::Expr>>(parameters);
	}
	throw ltnc::error::unopenedParameterList(parsePkg);
}


std::shared_ptr<ltnc::ExprCall> ltnc::parse::call(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::ARROW)) {
		Namespace ns = nameSpace(parsePkg);
		// function name
		if(parsePkg.match(TokenType::IDENTIFIER)) {
			std::string name = parsePkg.prev().string;
			auto params = parameters(parsePkg);
			return std::make_shared<ExprCall>(name, ns, params);
		}
		throw error::expectedIdentifier(parsePkg);
	}
	return nullptr;
}