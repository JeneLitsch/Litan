#include "LtncParserFunctions.hxx"

std::vector<std::unique_ptr<ltnc::StmtVar>> parseMembers(ltnc::ParserPackage & parsePkg) {
	std::vector<std::unique_ptr<ltnc::StmtVar>> members;
	if(parsePkg.match(ltnc::TokenType::L_BRACE)) {
		while(true) {
			try {
				auto member = ltnc::parse::declareVar(parsePkg);
				if(!member) break;
				members.push_back(std::move(member));
			}
			catch (const ltn::Error & error) {
				parsePkg.error << error;
				parsePkg.resync({
					ltnc::TokenType::VAR,
					ltnc::TokenType::R_BRACE});
			}
		}
		if(parsePkg.match(ltnc::TokenType::R_BRACE)) {
			return members;
		}
		throw ltnc::error::expectedBraceR(parsePkg);
	}
	throw ltnc::error::expectedBraceL(parsePkg);
}

ltnc::TypeId parseTypeId(ltnc::ParserPackage & parsePkg) {
	if(parsePkg.match(ltnc::TokenType::IDENTIFIER)) {
		return ltnc::TypeId(parsePkg.prev().string, parsePkg.ns);
	}
	throw ltnc::error::unnamedStruct(parsePkg);
}

std::unique_ptr<ltnc::DeclStruct> ltnc::parse::declareStruct(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::STRUCT)) {
		auto debugInfo = parsePkg.prev().debugInfo; 
		auto typeId = parseTypeId(parsePkg);
		auto members = parseMembers(parsePkg);
		return std::make_unique<DeclStruct>(
			debugInfo,
			typeId,
			std::move(members));
	}
	return nullptr;
}
