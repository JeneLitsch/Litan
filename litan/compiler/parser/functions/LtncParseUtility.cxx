#include "LtncParserFunctions.hxx"



ltn::c::Namespace ltn::c::parse::nameSpace(ParserPackage & parsePkg) {
	Namespace ns;
	while(parsePkg.match(TokenType::IDENTIFIER)) {
		ns.push(parsePkg.prev().string);
		if(!parsePkg.match(TokenType::DOUBLE_COLON)) {
			ns.pop();
			parsePkg.back();
			return ns;
		}
	}
	throw error::expectedIdentifier(parsePkg);
}

ltn::c::TypeId ltn::c::parse::typeId(ParserPackage & parsePkg) {
	Namespace ns = nameSpace(parsePkg);
	if(parsePkg.match(TokenType::IDENTIFIER)) {
		return TypeId(parsePkg.prev().string, ns);
	}
	throw error::expectedIdentifier(parsePkg);
}

ltn::c::Symbol ltn::c::parse::functionSymbol(ParserPackage & parsePkg) {
	Namespace ns = nameSpace(parsePkg);
	if(parsePkg.match(TokenType::IDENTIFIER)) {
		return Symbol(parsePkg.prev().string, ns);
	}
	throw error::expectedIdentifier(parsePkg);
}
