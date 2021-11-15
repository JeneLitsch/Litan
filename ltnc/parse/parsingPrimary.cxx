#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	std::unique_ptr<ast::Expression> paren(lex::Lexer & lexer) {
		if(!lexer.match(TT::PAREN_L)) {
			throw CompilerError{"expected (", lexer.inLine()};
		}
		auto expr = expression(lexer);
		if(!lexer.match(TT::PAREN_R)) {
			throw CompilerError{"expected )", lexer.inLine()};
		}
		return expr;
	}

	std::unique_ptr<ast::Integer> integer(lex::Lexer & lexer) {
		if(auto token = lexer.match(TT::INTEGER)) {
			std::stringstream ss;
			std::int64_t value;
			ss << token->str;
			ss >> value;
			return std::make_unique<ast::Integer>(value); 
		}
		return nullptr;
	}

	std::unique_ptr<ast::Float> floating(lex::Lexer & lexer) {
		if(auto token = lexer.match(TT::FLOAT)) {
			std::stringstream ss;
			double value;
			ss << token->str;
			ss >> value;
			return std::make_unique<ast::Float>(value); 
		}
		return nullptr;
	}

	std::unique_ptr<ast::Bool> boolean(lex::Lexer & lexer) {
		if(auto token = lexer.match(TT::TRUE)) {
			return std::make_unique<ast::Bool>(true); 
		}
		if(auto token = lexer.match(TT::FALSE)) {
			return std::make_unique<ast::Bool>(false); 
		}
		return nullptr;
	}

	std::unique_ptr<ast::Expression> primary(lex::Lexer & lexer) {
		if(auto expr = integer(lexer)) return expr;
		if(auto expr = floating(lexer)) return expr;
		if(auto expr = boolean(lexer)) return expr;
		if(auto expr = paren(lexer)) return expr;
		throw CompilerError{"Invalid Expression", lexer.inLine()};
	}
}
