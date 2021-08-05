#include "LtncParserFunctions.hxx"
#include <functional>

namespace ltnc {
	namespace parse {
		using ExprFx = std::function<std::shared_ptr<Expr>(ParserPackage & parsePkg)>; 
		std::shared_ptr<ltnc::Expr> binary(
			const std::vector<TokenType> & acceptedTokens,
			const ExprFx & nextPresedence,
			ParserPackage & parsePkg) {
			

			std::shared_ptr<ltnc::Expr> l = nextPresedence(parsePkg);
			while(parsePkg.match(acceptedTokens)) {
				Token op = parsePkg.prev();
				std::shared_ptr<ltnc::Expr> r = nextPresedence(parsePkg);
				l = std::make_shared<ExprBinary>(op.debugInfo, op.type, l, r);
			}
			return l;
		}
	}
}

std::shared_ptr<ltnc::Expr> ltnc::parse::expression(ParserPackage & parsePkg) {
	return logicAnd(parsePkg);
}

std::shared_ptr<ltnc::Expr> ltnc::parse::logicAnd(ParserPackage & parsePkg) {
	return binary({ TokenType::LOG_AND }, logicOr, parsePkg);
}

std::shared_ptr<ltnc::Expr> ltnc::parse::logicOr(ParserPackage & parsePkg) {
	return binary({ TokenType::LOG_OR }, equality, parsePkg);
}

std::shared_ptr<ltnc::Expr> ltnc::parse::equality(ParserPackage & parsePkg) {
	return binary(
		{ TokenType::EQUAL, TokenType::UNEQUAL },
		comparison,
		parsePkg);
}

std::shared_ptr<ltnc::Expr> ltnc::parse::comparison(ParserPackage & parsePkg) {
	return binary(
		{ 	TokenType::BIGGER, TokenType::BIGGEREQUAL,
			TokenType::SMALLER, TokenType::SMALLEREQUAL },
		threeWay,
		parsePkg);
}

std::shared_ptr<ltnc::Expr> ltnc::parse::threeWay(ParserPackage & parsePkg) {
	return binary(
		{ 	TokenType::SPACESHIP },
		term,
		parsePkg);
}

std::shared_ptr<ltnc::Expr> ltnc::parse::term(ParserPackage & parsePkg) {
	return binary(
		{ TokenType::PLUS, TokenType::MINUS },
		product,
		parsePkg);
}


std::shared_ptr<ltnc::Expr> ltnc::parse::product(ParserPackage & parsePkg) {
	return binary(
		{ TokenType::STAR, TokenType::SLASH, TokenType::MOD },
		exponent,
		parsePkg);
}

std::shared_ptr<ltnc::Expr> ltnc::parse::exponent(ParserPackage & parsePkg) {
	return binary(
		{ TokenType::POWER },
		unary,
		parsePkg);
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