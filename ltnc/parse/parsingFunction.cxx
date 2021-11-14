#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"
#include <iostream>

// The following functions are for parsing the head of function
// function foo(Type name, ...) -> RType

namespace ltnc::parse {
	namespace {
		using TT = ltnc::lex::Token::Type;
		using Parameter = std::tuple<std::string, std::string>;
		using Parameters = std::vector<Parameter>;

		std::string indentifier(lex::Lexer & lexer, const std::string & errMsg){
			if(auto token = lexer.match(TT::INDENTIFIER)) {
				return token->str;
			}
			throw ltnc::CompilerError{errMsg, lexer.inLine()};
		}

		// return type of paramter
		std::string parameterType(lex::Lexer & lexer) {
			return indentifier(lexer, "expected parameter");
		}

		// return name of paramter
		std::string parameterName(lex::Lexer & lexer) {
			return indentifier(lexer, "expected parameter name");
		}

		// return function name
		std::string functionName(lex::Lexer & lexer) {
			return indentifier(lexer, "expected function name");
		}


		// Returns a array of all parameters
		Parameters parameterList(lex::Lexer & lexer) {
			if(!lexer.match(TT::PAREN_L)) {
				throw ltnc::CompilerError{"mission (", lexer.inLine()};
			}
			
			Parameters parameters{};
			if(!lexer.match(TT::PAREN_R)) {
				while(true) {
					const auto type = parameterType(lexer);
					const auto name = parameterName(lexer);
					parameters.push_back(Parameter{type, name});
					std::cout << type << " " << name << " "; 
					if(lexer.match(TT::PAREN_R)) break;
					if(!lexer.match(TT::COMMA)) {
						throw ltnc::CompilerError{"expected comma between parameters", lexer.inLine()};
					}
				}
			} 
			std::cout << "\n";
			return parameters;
		}


		// returns return type
		std::string returnType(lex::Lexer & lexer) {
			if(lexer.match(TT::ARROW)) {
				return indentifier(lexer, "expected return type");
			}
			throw ltnc::CompilerError{"expected ->", lexer.inLine()};
		}
	}

	// parses and returns a function node
	std::unique_ptr<ast::Function> function(lex::Lexer & lexer) {
		if(lexer.match(TT::FUNCTION)) {
			const auto name = functionName(lexer);
			const auto parameters = parameterList(lexer);
			const auto returnT = returnType(lexer);
			auto body = statement(lexer); 
			return std::make_unique<ast::Function>(name, returnT, parameters, std::move(body));
		}
		return nullptr;
	}
}