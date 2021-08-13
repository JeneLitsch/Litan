#include "LtncParserFunctions.hxx"

std::vector<std::unique_ptr<ltn::c::StmtVar>> parseMembers(ltn::c::ParserPackage & parsePkg) {
	std::vector<std::unique_ptr<ltn::c::StmtVar>> members;
	if(parsePkg.match(ltn::c::TokenType::L_BRACE)) {
		while(true) {
			try {
				auto member = ltn::c::parse::declareVar(parsePkg);
				if(!member) break;
				members.push_back(std::move(member));
			}
			catch (const ltn::Error & error) {
				parsePkg.error << error;
				parsePkg.resync({
					ltn::c::TokenType::VAR,
					ltn::c::TokenType::R_BRACE});
			}
		}
		if(parsePkg.match(ltn::c::TokenType::R_BRACE)) {
			return members;
		}
		throw ltn::c::error::expectedBraceR(parsePkg);
	}
	throw ltn::c::error::expectedBraceL(parsePkg);
}

ltn::c::TypeId parseTypeId(ltn::c::ParserPackage & parsePkg) {
	if(parsePkg.match(ltn::c::TokenType::IDENTIFIER)) {
		return ltn::c::TypeId(parsePkg.prev().string, parsePkg.ns);
	}
	throw ltn::c::error::unnamedStruct(parsePkg);
}

std::unique_ptr<ltn::c::DeclStruct> ltn::c::parse::declareStruct(ParserPackage & parsePkg) {
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
