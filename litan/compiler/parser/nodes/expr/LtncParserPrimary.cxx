#include "LtncParserPrimary.hxx"

void ltnc::ParserPrimary::connect(const ParserNode<ExprCall> & call) {
	this->call = &call;
}

std::shared_ptr<ltnc::Expr> ltnc::ParserPrimary::eval(ParserPackage & parsePkg) const  {
	// literals
	if (parsePkg.match(TokenType::INT_LITERAL)) {
		std::int64_t value = std::stoll(parsePkg.prev().string);
		return std::make_shared<ExprIntLiteral>(value);
	}
	if (parsePkg.match(TokenType::FLOAT_LITERAL)) {
		double value = std::stod(parsePkg.prev().string);
		return std::make_shared<ExprFltLiteral>(value);
	}
	if (parsePkg.match(TokenType::STRING_LITERAL)) {
		std::string value = parsePkg.prev().string;
		return std::make_shared<ExprStrLiteral>(value);
	}

	// variables and constants
	if (parsePkg.match(TokenType::IDENTIFIER)) {
		std::string name = parsePkg.prev().string;
		return std::make_shared<ExprVar>(name);
	}

	// call function
	if (parsePkg.match(TokenType::CALL)) {
		return this->call->eval(parsePkg);
	}
	return parsePkg.error("No matching expression");
}
