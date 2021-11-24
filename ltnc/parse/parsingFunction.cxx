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
					parameters.push_back(parameterName(lexer));
					if(lexer.match(TT::PAREN_R)) break;
					if(!lexer.match(TT::COMMA)) {
						throw ltn::c::CompilerError{"expected comma between parameters", lexer.inLine()};
					}
				}
			} 
			return parameters;
		}

		ast::Parameters instructions(lex::Lexer & lexer) {
			if(!lexer.match(TT::BRACE_L)) {
				throw ltn::c::CompilerError{"missing {", lexer.inLine()};
			}
			
			std::vector<std::string> insts{};
			if(!lexer.match(TT::BRACE_R)) {
				while(!lexer.match(TT::BRACE_R)) {
					if(auto str = lexer.match(TT::STRING)) {
						insts.push_back(str->str);
					}
					else {
						throw CompilerError{
							"Expected instruction between \"...\"",
							lexer.inLine() };
					}
				}
			} 
			return insts;
		}

		// parses and returns a function node
		std::unique_ptr<ast::Function> function(
			lex::Lexer & lexer,
			const ast::Namespace & nameSpace) {
			const auto name = functionName(lexer);
			const auto parameters = parameterList(lexer);
			auto body = statement(lexer); 
			return std::make_unique<ast::Function>(
				name,
				nameSpace,
				parameters,
				std::move(body),
				lexer.debug());
		}

		// parses and returns a asm function node
		std::unique_ptr<ast::Asm> asmFunction(
			lex::Lexer & lexer,
			const ast::Namespace & nameSpace) {
			const auto name = functionName(lexer);
			const auto paramters = parameterList(lexer);
			const auto instructions = parse::instructions(lexer);
			return std::make_unique<ast::Asm>(
				name,
				nameSpace,
				paramters,
				instructions,
				lexer.debug());
		}
	}

	// parses and returns a functional node
	std::unique_ptr<ast::Functional> functional(
		lex::Lexer & lexer,
		const ast::Namespace & nameSpace) {
		if(lexer.match(TT::FUNCTION)) {
			return function(lexer, nameSpace);
		}
		if(lexer.match(TT::ASM)) {
			return asmFunction(lexer, nameSpace);
		}
		return nullptr;

	}
}