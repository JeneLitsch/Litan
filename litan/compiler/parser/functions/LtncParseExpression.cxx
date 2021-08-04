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
		l = std::make_shared<ExprBinary>(op.debugInfo, op.type, l, r);
	}
	return l;
}


std::shared_ptr<ltnc::Expr> ltnc::parse::term(ParserPackage & parsePkg) {
	std::shared_ptr<ltnc::Expr> l = product(parsePkg);
	while(parsePkg.match({TokenType::PLUS, TokenType::MINUS})) {
		Token op = parsePkg.prev();
		std::shared_ptr<ltnc::Expr> r = product(parsePkg);
		l = std::make_shared<ExprBinary>(op.debugInfo, op.type, l, r);
	}
	return l;
}


std::shared_ptr<ltnc::Expr> ltnc::parse::product(ParserPackage & parsePkg) {
	std::shared_ptr<ltnc::Expr> l = unary(parsePkg);
	while(parsePkg.match({TokenType::STAR, TokenType::SLASH, TokenType::MOD})) {
		Token op = parsePkg.prev();
		std::shared_ptr<ltnc::Expr> r = unary(parsePkg);
		l = std::make_shared<ExprBinary>(op.debugInfo, op.type, l, r);
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
		return std::make_shared<ExprUnary>(op.debugInfo, op.type, r);
	}
	return primary(parsePkg);	
}

std::shared_ptr<ltnc::Expr> ltnc::parse::primary(ParserPackage & parsePkg) {
	// literals
	if(auto literal = intLiteral(parsePkg)) return literal;
	if(auto literal = floatLiteral(parsePkg)) return literal;
	if(auto literal = stringLiteral(parsePkg)) return literal;
	if(auto literal = nulLiteral(parsePkg)) return literal;
	if(auto literal = boolLiteral(parsePkg)) return literal;

	if (parsePkg.match(TokenType::L_PAREN)) {
		auto expr_ = expression(parsePkg);
		if (parsePkg.match(TokenType::R_PAREN)) {
			return expr_;
		}
		throw error::expectedParenR(parsePkg);
	}

	if (auto expr = call(parsePkg)) {
		return expr;
	}

	if (auto expr = var(parsePkg)) {
		return expr;
	}
	throw error::expectedExpression(parsePkg);
}