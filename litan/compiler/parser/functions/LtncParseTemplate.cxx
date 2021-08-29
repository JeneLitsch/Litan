#include "LtncParserFunctions.hxx"

std::vector<std::string> parseTemplateParameters(ltn::c::ParserPackage & parsePkg) {
	std::vector<std::string> placeholders;
	do  {
		if(parsePkg.match(ltn::c::TokenType::IDENTIFIER)) {
			placeholders.push_back(parsePkg.prev().string);
		}
		else {
			throw ltn::c::error::expectedIdentifier(parsePkg.curr().debugInfo);
		}
	} while(parsePkg.match(ltn::c::TokenType::COMMA));
	return placeholders;
}

std::unique_ptr<ltn::c::DeclTemplate> ltn::c::parse::declareTemplate(
	ParserPackage & parsePkg) {
	
	if(parsePkg.match(TokenType::TEMPLATE)) {
		DebugInfo debugInfo = parsePkg.prev().debugInfo;
		if (parsePkg.match(TokenType::SMALLER)) {
			std::vector<std::string> placeholders = parseTemplateParameters(parsePkg);
			if (parsePkg.match(TokenType::BIGGER)) {
				if(auto function = declareFunction(parsePkg)){
					return std::make_unique<DeclTemplateFunction>(
						debugInfo, std::move(placeholders), std::move(function));
				}
				else if (auto structDecl = declareStruct(parsePkg)) {
					return std::make_unique<DeclTemplateStruct>(
						debugInfo, std::move(placeholders), std::move(structDecl));
				}
				throw error::expectedDeclaration(debugInfo);
			}
			throw Error(ErrorCode::MISC, "Expected >", debugInfo);
		}
		throw Error(ErrorCode::MISC, "Expected <", debugInfo);
	}
	return nullptr;
}