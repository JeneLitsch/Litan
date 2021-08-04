#include "LtncParserFunctions.hxx"

std::shared_ptr<ltnc::Expr> ltnc::parse::intLiteral(ParserPackage & parsePkg) {
	if (parsePkg.match(ltnc::TokenType::INT_LITERAL)) {
		std::int64_t value = std::stoll(parsePkg.prev().string);
		return std::make_shared<ExprIntLiteral>(
			parsePkg.prev().debugInfo,
			value);
	}
	return nullptr;
}

std::shared_ptr<ltnc::Expr> ltnc::parse::floatLiteral(ParserPackage & parsePkg) {
	if (parsePkg.match(TokenType::FLOAT_LITERAL)) {
		double value = std::stod(parsePkg.prev().string);
		return std::make_shared<ExprFltLiteral>(
			parsePkg.prev().debugInfo,
			value);
	}
	return nullptr;
}

std::shared_ptr<ltnc::Expr> ltnc::parse::stringLiteral(ParserPackage & parsePkg) {
	if (parsePkg.match(TokenType::STRING_LITERAL)) {
		std::string value = parsePkg.prev().string;
		return std::make_shared<ExprStrLiteral>(
			parsePkg.prev().debugInfo,
			value);
	}
	return nullptr;
}

std::shared_ptr<ltnc::Expr> ltnc::parse::nulLiteral(ParserPackage & parsePkg) {
	if (parsePkg.match(TokenType::NUL)) {
		return std::make_shared<ExprNul>(parsePkg.prev().debugInfo);
	}
	return nullptr;
}

