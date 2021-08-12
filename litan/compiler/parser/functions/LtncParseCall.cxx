#include "LtncParserFunctions.hxx"

auto parameters(ltnc::ParserPackage & parsePkg) {
	// parameters
	if (parsePkg.match(ltnc::TokenType::L_PAREN)) {
		std::vector<std::unique_ptr<ltnc::Expr>> parameters;
		if (!parsePkg.match(ltnc::TokenType::R_PAREN)) {
			while(!parsePkg.isAtEnd()) {
				auto expr = ltnc::parse::expression(parsePkg);
				parameters.push_back(std::move(expr));
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
		return parameters;
	}
	throw ltnc::error::unopenedParameterList(parsePkg);
}


std::unique_ptr<ltnc::ExprCall> ltnc::parse::call(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::ARROW)) {
		const auto & debugInfo = parsePkg.prev().debugInfo;
		Namespace ns = nameSpace(parsePkg);
		// function name
		if(parsePkg.match(TokenType::IDENTIFIER)) {
			std::string name = parsePkg.prev().string;
			auto params = parameters(parsePkg);
			return std::make_unique<ExprCall>(debugInfo, name, ns, std::move(params));
		}
		throw error::expectedIdentifier(parsePkg);
	}
	return nullptr;
}