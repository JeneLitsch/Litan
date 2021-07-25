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
	throw std::runtime_error("Expected idendifier");
}

ltnc::TypeId ltnc::parse::type(ParserPackage & parsePkg) {
	Namespace ns = nameSpace(parsePkg);
	if(parsePkg.match(TokenType::IDENTIFIER)) {
		return TypeId(parsePkg.prev().string, ns);
	}
	throw parsePkg.error("Invalid Type");
}
