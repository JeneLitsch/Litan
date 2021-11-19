#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"
#include <iostream>

// The following functions are for parsing the head of function
// function foo(Type name, ...) -> RType

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;

		// Returns a array of all parameters
		ast::Parameters parameterList(lex::Lexer & lexer) {
			if(!lexer.match(TT::PAREN_L)) {
				throw ltn::c::CompilerError{"missing (", lexer.inLine()};
			}
			
			ast::Parameters parameters{};
			if(!lexer.match(TT::PAREN_R)) {
				while(true) {
					const auto type = parse::type(lexer);
					const auto name = parameterName(lexer);
					ast::Parameter param {type, name};
					parameters.push_back(param);
					if(lexer.match(TT::PAREN_R)) break;
					if(!lexer.match(TT::COMMA)) {
						throw ltn::c::CompilerError{"expected comma between parameters", lexer.inLine()};
					}
				}
			} 
			return parameters;
		}


		// returns return type
		auto returnType(lex::Lexer & lexer) {
			if(lexer.match(TT::ARROW)) {
				return type(lexer);
			}
			throw ltn::c::CompilerError{"expected ->", lexer.inLine()};
		}
	}

	// parses and returns a function node
	std::unique_ptr<ast::Function> function(lex::Lexer & lexer) {
		if(lexer.match(TT::FUNCTION)) {
			const auto name = functionName(lexer);
			auto && parameters = parameterList(lexer);
			auto && returnType = parse::returnType(lexer);
			auto && body = statement(lexer); 
			return std::make_unique<ast::Function>(
				name,
				std::move(returnType),
				std::move(parameters),
				std::move(body),
				lexer.debug());
		}
		return nullptr;
	}
}