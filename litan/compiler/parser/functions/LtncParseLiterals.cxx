#include "LtncParserFunctions.hxx"



std::unique_ptr<ltn::c::Expr> ltn::c::parse::intLiteral(ParserPackage & parsePkg) {
	if (parsePkg.match(ltn::c::TokenType::INT_LITERAL)) {
		std::int64_t value = std::stoll(parsePkg.prev().string);
		return std::make_unique<ExprLiteral>(
			parsePkg.prev().debugInfo,
			value);
	}
	return nullptr;
}

std::unique_ptr<ltn::c::Expr> ltn::c::parse::floatLiteral(ParserPackage & parsePkg) {
	if (parsePkg.match(TokenType::FLOAT_LITERAL)) {
		double value = std::stod(parsePkg.prev().string);
		return std::make_unique<ExprLiteral>(
			parsePkg.prev().debugInfo,
			value);
	}
	return nullptr;
}

std::unique_ptr<ltn::c::Expr> ltn::c::parse::stringLiteral(ParserPackage & parsePkg) {
	if (parsePkg.match(TokenType::STRING_LITERAL)) {
		std::string value = parsePkg.prev().string;
		return std::make_unique<ExprLiteral>(
			parsePkg.prev().debugInfo,
			value);
	}
	return nullptr;
}

std::unique_ptr<ltn::c::Expr> ltn::c::parse::nulLiteral(ParserPackage & parsePkg) {
	if (parsePkg.match(TokenType::NUL)) {
		return std::make_unique<ExprLiteral>(
			parsePkg.prev().debugInfo,
			std::monostate());
	}
	return nullptr;
}

std::unique_ptr<ltn::c::Expr> ltn::c::parse::boolLiteral(ParserPackage & parsePkg) {
	if (parsePkg.match(TokenType::TRUE)) {
		return std::make_unique<ExprLiteral>(
			parsePkg.prev().debugInfo,
			true);
	}
	if (parsePkg.match(TokenType::FALSE)) {
		return std::make_unique<ExprLiteral>(
			parsePkg.prev().debugInfo,
			false);
	}
	return nullptr;
}