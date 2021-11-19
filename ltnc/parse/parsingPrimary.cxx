#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		using NT = ast::New::Type;
	}

	std::unique_ptr<ast::Expression> paren(lex::Lexer & lexer) {
		if(lexer.match(TT::PAREN_L)) {
			auto expr = expression(lexer);
			if(!lexer.match(TT::PAREN_R)) {
				throw CompilerError{"expected )", lexer.inLine()};
			}
			return expr;
		}
		return nullptr;
	}

	std::unique_ptr<ast::Integer> integer(lex::Lexer & lexer) {
		if(auto token = lexer.match(TT::INTEGER)) {
			std::stringstream ss;
			std::int64_t value;
			ss << token->str;
			ss >> value;
			return std::make_unique<ast::Integer>(value, lexer.debug()); 
		}
		return nullptr;
	}

	std::unique_ptr<ast::Float> floating(lex::Lexer & lexer) {
		if(auto token = lexer.match(TT::FLOAT)) {
			std::stringstream ss;
			double value;
			ss << token->str;
			ss >> value;
			return std::make_unique<ast::Float>(value, lexer.debug()); 
		}
		return nullptr;
	}

	std::unique_ptr<ast::Bool> boolean(lex::Lexer & lexer) {
		if(auto token = lexer.match(TT::TRUE)) {
			return std::make_unique<ast::Bool>(true, lexer.debug()); 
		}
		if(auto token = lexer.match(TT::FALSE)) {
			return std::make_unique<ast::Bool>(false, lexer.debug()); 
		}
		return nullptr;
	}

	std::unique_ptr<ast::New> newObject(lex::Lexer & lexer) {
		if(lexer.match(TT::NEW)) {
			if(auto type = lexer.match(TT::INDENTIFIER)) {
				if(type->str == "Array") {
					return std::make_unique<ast::New>(lexer.debug(), NT::ARRAY);
				}
				if(type->str == "Map") {
					return std::make_unique<ast::New>(lexer.debug(), NT::MAP);
				}
			}
		}
		return nullptr;
	}

	std::unique_ptr<ast::Var> variable(lex::Lexer & lexer) {
		const auto name = parse::variableName(lexer);
		return std::make_unique<ast::Var>(name, lexer.debug());
	}

	std::unique_ptr<ast::Expression> primary(lex::Lexer & lexer) {
		if(auto expr = integer(lexer)) return expr;
		if(auto expr = floating(lexer)) return expr;
		if(auto expr = boolean(lexer)) return expr;
		if(auto expr = paren(lexer)) return expr;
		if(auto expr = newObject(lexer)) return expr;
		return variable(lexer);
	}
}

