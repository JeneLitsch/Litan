#include "LtncParserFunctions.hxx"

std::shared_ptr<ltnc::Expr> ltnc::parse::expression(ParserPackage & parsePkg) {
	return comparison(parsePkg);
}


std::shared_ptr<ltnc::Expr> ltnc::parse::comparison(ParserPackage & parsePkg) {
	std::shared_ptr<ltnc::Expr> l = term(parsePkg);
	while(parsePkg.match({
		TokenType::EQUAL,
		TokenType::UNEQUAL,
		TokenType::BIGGER,
		TokenType::BIGGEREQUAL,
		TokenType::SMALLER,
		TokenType::SMALLEREQUAL})) {
		
		Token op = parsePkg.prev();
		std::shared_ptr<ltnc::Expr> r = term(parsePkg);
		l = std::make_shared<ExprBinary>(op.type, l, r);
	}
	return l;
}


std::shared_ptr<ltnc::Expr> ltnc::parse::term(ParserPackage & parsePkg) {
	std::shared_ptr<ltnc::Expr> l = product(parsePkg);
	while(parsePkg.match({TokenType::PLUS, TokenType::MINUS})) {
		Token op = parsePkg.prev();
		std::shared_ptr<ltnc::Expr> r = product(parsePkg);
		l = std::make_shared<ExprBinary>(op.type, l, r);
	}
	return l;
}


std::shared_ptr<ltnc::Expr> ltnc::parse::product(ParserPackage & parsePkg) {
	std::shared_ptr<ltnc::Expr> l = unary(parsePkg);
	while(parsePkg.match({TokenType::STAR, TokenType::SLASH, TokenType::MOD})) {
		Token op = parsePkg.prev();
		std::shared_ptr<ltnc::Expr> r = unary(parsePkg);
		l = std::make_shared<ExprBinary>(op.type, l, r);
	}
	return l;
}


std::shared_ptr<ltnc::Expr> ltnc::parse::unary(ParserPackage & parsePkg) {
	if(parsePkg.match({
		TokenType::MINUS,
		TokenType::LOG_NOT,
		TokenType::BIT_NOT,
		TokenType::COPY})) {
		Token op = parsePkg.prev();
		std::shared_ptr<ltnc::Expr> r = unary(parsePkg);
		return std::make_shared<ExprUnary>(op.type, r);
	}
	return primary(parsePkg);	
}


std::shared_ptr<ltnc::Expr> ltnc::parse::primary(ParserPackage & parsePkg) {
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

	if (parsePkg.match(TokenType::NUL)) {
		return std::make_shared<ExprNul>();
	}

	if (parsePkg.match(TokenType::L_PAREN)) {
		auto expr_ = expression(parsePkg);
		if (!parsePkg.match(TokenType::R_PAREN)) {
			return parsePkg.error("Expected )");
		}
		return expr_;
	}

	// call function
	if (auto expr = call(parsePkg)) {
		return expr;
	}

	// variables and constants
	if (auto expr = var(parsePkg)) {
		return expr;
	}
	return parsePkg.error("No matching expression");
}