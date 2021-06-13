#include "LtncParserPrimary.hxx"

void ltnc::ParserPrimary::connect(
	const ParserNode<ExprCall> & call,
	const ParserNode<ExprVar> & var) {
	
	this->call = &call;
	this->var = &var;
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
	if (auto expr = this->var->eval(parsePkg)) return expr;

	// call function
	if (parsePkg.match(TokenType::CALL)) {
		return this->call->eval(parsePkg);
	}
	return parsePkg.error("No matching expression");
}
