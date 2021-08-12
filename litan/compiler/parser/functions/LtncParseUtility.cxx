#include "LtncParserFunctions.hxx"



ltnc::Namespace ltnc::parse::nameSpace(ParserPackage & parsePkg) {
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

ltnc::TypeId ltnc::parse::typeId(ParserPackage & parsePkg) {
	Namespace ns = nameSpace(parsePkg);
	if(parsePkg.match(TokenType::IDENTIFIER)) {
		return TypeId(parsePkg.prev().string, ns);
	}
	throw error::expectedIdentifier(parsePkg);
}

ltnc::Symbol ltnc::parse::functionSymbol(ParserPackage & parsePkg) {
	Namespace ns = nameSpace(parsePkg);
	if(parsePkg.match(TokenType::IDENTIFIER)) {
		return Symbol(parsePkg.prev().string, ns);
	}
	throw error::expectedIdentifier(parsePkg);
}
