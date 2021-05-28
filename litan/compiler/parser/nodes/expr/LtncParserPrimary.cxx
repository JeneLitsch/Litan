#include "LtncParserPrimary.hxx"

void ltnc::ParserPrimary::connect(const ParserNode<ExprCall> & call) {
	this->call = &call;
}

std::shared_ptr<ltnc::Expr> ltnc::ParserPrimary::eval(ParserPackage & parsePkg) const  {
	if (parsePkg.match(TokenType::NUMBER_INT)) {
		std::int64_t value = std::stoll(parsePkg.prev().string);
		return std::make_shared<ExprIntLiteral>(value);
	}
	if (parsePkg.match(TokenType::NUMBER_FLT)) {
		double value = std::stod(parsePkg.prev().string);
		return std::make_shared<ExprFltLiteral>(value);
	}
	if (parsePkg.match(TokenType::IDENTIFIER)) {
		std::string name = parsePkg.prev().string;
		return std::make_shared<ExprVar>(name);
	}
	if (parsePkg.match(TokenType::CALL)) {
		return this->call->eval(parsePkg);
	}
	return parsePkg.error("No matching expression");
}
