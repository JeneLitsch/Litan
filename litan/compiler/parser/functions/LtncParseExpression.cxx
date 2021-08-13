#include "LtncParserFunctions.hxx"
#include <functional>

namespace ltn::c {
	namespace parse {
		using ExprFx = std::function<std::unique_ptr<Expr>(ParserPackage & parsePkg)>; 
		std::unique_ptr<ltn::c::Expr> binary(
			const std::vector<TokenType> & acceptedTokens,
			const ExprFx & nextPresedence,
			ParserPackage & parsePkg) {
			

			std::unique_ptr<ltn::c::Expr> l = nextPresedence(parsePkg);
			while(parsePkg.match(acceptedTokens)) {
				Token op = parsePkg.prev();
				std::unique_ptr<ltn::c::Expr> r = nextPresedence(parsePkg);
				auto expr = std::make_unique<ExprBinary>(op.debugInfo, op.type, std::move(l), std::move(r));
				l = std::move(expr);
			}
			return l;
		}
	}
}

std::unique_ptr<ltn::c::Expr> ltn::c::parse::expression(ParserPackage & parsePkg) {
	return logicAnd(parsePkg);
}

std::unique_ptr<ltn::c::Expr> ltn::c::parse::logicAnd(ParserPackage & parsePkg) {
	return binary({ TokenType::LOG_AND }, logicOr, parsePkg);
}

std::unique_ptr<ltn::c::Expr> ltn::c::parse::logicOr(ParserPackage & parsePkg) {
	return binary({ TokenType::LOG_OR }, equality, parsePkg);
}

std::unique_ptr<ltn::c::Expr> ltn::c::parse::equality(ParserPackage & parsePkg) {
	return binary(
		{ TokenType::EQUAL, TokenType::UNEQUAL },
		comparison,
		parsePkg);
}

std::unique_ptr<ltn::c::Expr> ltn::c::parse::comparison(ParserPackage & parsePkg) {
	return binary(
		{ 	TokenType::BIGGER, TokenType::BIGGEREQUAL,
			TokenType::SMALLER, TokenType::SMALLEREQUAL },
		threeWay,
		parsePkg);
}

std::unique_ptr<ltn::c::Expr> ltn::c::parse::threeWay(ParserPackage & parsePkg) {
	return binary(
		{ 	TokenType::SPACESHIP },
		term,
		parsePkg);
}

std::unique_ptr<ltn::c::Expr> ltn::c::parse::term(ParserPackage & parsePkg) {
	return binary(
		{ TokenType::PLUS, TokenType::MINUS },
		product,
		parsePkg);
}


std::unique_ptr<ltn::c::Expr> ltn::c::parse::product(ParserPackage & parsePkg) {
	return binary(
		{ TokenType::STAR, TokenType::SLASH, TokenType::MOD },
		exponent,
		parsePkg);
}

std::unique_ptr<ltn::c::Expr> ltn::c::parse::exponent(ParserPackage & parsePkg) {
	return binary(
		{ TokenType::POWER },
		unary,
		parsePkg);
}


std::unique_ptr<ltn::c::Expr> ltn::c::parse::unary(ParserPackage & parsePkg) {
	if(parsePkg.match({
		TokenType::MINUS,
		TokenType::LOG_NOT,
		TokenType::BIT_NOT,
		TokenType::COPY})) {
		Token op = parsePkg.prev();
		std::unique_ptr<ltn::c::Expr> r = unary(parsePkg);
		return std::make_unique<ExprUnary>(op.debugInfo, op.type, std::move(r));
	}
	return primary(parsePkg);	
}

std::unique_ptr<ltn::c::Expr> ltn::c::parse::primary(ParserPackage & parsePkg) {
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