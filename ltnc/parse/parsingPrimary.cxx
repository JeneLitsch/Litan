#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;

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

		std::unique_ptr<ast::Literal> array(lex::Lexer & lexer) {
			std::vector<std::unique_ptr<ast::Expression>> initElements;
			if(!lexer.match(TT::BRACKET_R)) {
				while(true) {
					if(lexer.match(TT::___EOF___)) {
						throw CompilerError{"Expected ]", lexer.inLine()};
					}
					initElements.push_back(expression(lexer));
					if(lexer.match(TT::BRACKET_R)) break;
					if(!lexer.match(TT::COMMA)) {
						throw CompilerError{"Expected ,", lexer.inLine()};
					}
				}
			}
			return std::make_unique<ast::Array>(
				std::move(initElements),
				lexer.debug());
		}

		std::unique_ptr<ast::Literal> newObject(lex::Lexer & lexer) {
			if(auto token = lexer.match(TT::STRING)) {
				return std::make_unique<ast::String>(token->str, lexer.debug()); 
			}
			if(lexer.match(TT::BRACKET_L)) {
				return array(lexer);
			}
			return nullptr;
		}

		auto parameters(lex::Lexer & lexer) {
			if(lexer.match(TT::PAREN_L)) {
				std::vector<std::unique_ptr<ast::Expression>> parameters;
				if(lexer.match(TT::PAREN_R)) {
					return parameters;
				}
				while(true) {
					parameters.push_back(expression(lexer));
					if(lexer.match(TT::PAREN_R)) {
						return parameters;
					}
					if(!lexer.match(TT::COMMA)) {
						throw CompilerError{"Missing ,", lexer.inLine()};
					}
				}
			}
			throw CompilerError{"Missing ( after function name", lexer.inLine()};
		}

		std::unique_ptr<ast::Call> call(lex::Lexer & lexer) {
			if(auto callOp = lexer.match(TT::ARROW)) {
				auto name = parse::functionName(lexer);
				auto parameters = parse::parameters(lexer);
				return std::make_unique<ast::Call>(
					name,
					std::move(parameters),
					lexer.debug());
			}
			return nullptr;
		}
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
		if(auto expr = call(lexer)) return expr;
		return variable(lexer);
	}
}

