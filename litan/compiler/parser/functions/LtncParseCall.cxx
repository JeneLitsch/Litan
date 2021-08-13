#include "LtncParserFunctions.hxx"

auto parameters(ltn::c::ParserPackage & parsePkg) {
	// parameters
	if (parsePkg.match(ltn::c::TokenType::L_PAREN)) {
		std::vector<std::unique_ptr<ltn::c::Expr>> parameters;
		if (!parsePkg.match(ltn::c::TokenType::R_PAREN)) {
			while(!parsePkg.isAtEnd()) {
				auto expr = ltn::c::parse::expression(parsePkg);
				parameters.push_back(std::move(expr));
				// next paramter
				if(parsePkg.match(ltn::c::TokenType::COMMA)) {
					continue;
				}
				// end list
				else if (parsePkg.match(ltn::c::TokenType::R_PAREN)) {
					break;
				}
				else {
					throw ltn::c::error::unclosedParameterList(parsePkg);
				}
			}
		}
		return parameters;
	}
	throw ltn::c::error::unopenedParameterList(parsePkg);
}


std::unique_ptr<ltn::c::ExprCall> ltn::c::parse::call(ParserPackage & parsePkg) {
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