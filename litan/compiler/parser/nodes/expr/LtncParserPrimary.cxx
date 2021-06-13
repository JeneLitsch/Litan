#include "LtncParserPrimary.hxx"

void ltnc::ParserPrimary::connect(
	const ParserNode<ExprCall> & call,
	const ParserNode<ExprVar> & var,
	const ParserNode<Expr> & expr) {
	
	this->call = &call;
	this->var = &var;
	this->expr = &expr;
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

	if (parsePkg.match(TokenType::L_PAREN)) {
		auto expr_ = this->expr->eval(parsePkg);
		if (!parsePkg.match(TokenType::R_PAREN)) {
			return parsePkg.error("Expected )");
		}
		return expr_;
	}

	// variables and constants
	if (auto expr = this->var->eval(parsePkg)) return expr;

	// call function
	if (parsePkg.match(TokenType::CALL)) {
		return this->call->eval(parsePkg);
	}
	return parsePkg.error("No matching expression");
}
