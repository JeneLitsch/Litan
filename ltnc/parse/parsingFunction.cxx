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
					parameters.push_back(parse::parameterName(lexer));
					if(lexer.match(TT::PAREN_R)) break;
					if(!lexer.match(TT::COMMA)) {
						throw CompilerError{
							"expected comma between parameters",
							lexer.inLine()};
					}
				}
			} 
			return parameters;
		}

		// Returns a array of all parameters
		std::vector<std::unique_ptr<ast::Var>> captures(lex::Lexer & lexer) {
			if(!lexer.match(TT::BRACKET_L)) {
				throw CompilerError{"missing [", lexer.inLine()};
			}
			
			std::vector<std::unique_ptr<ast::Var>> captures{};
			if(!lexer.match(TT::BRACKET_R)) {
				while(true) {
					const auto name = parse::variableName(lexer);
					captures.push_back(std::make_unique<ast::Var>(name, lexer.debug()));
					if(lexer.match(TT::BRACKET_R)) break;
					if(!lexer.match(TT::COMMA)) {
						throw CompilerError{
							"expected comma between captures",
							lexer.inLine()};
					}
				}
			} 
			return captures;
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
		template<class FunctionalNode>
		std::unique_ptr<FunctionalNode> functionalNode(
			lex::Lexer & lexer,
			const ast::Namespace & nameSpace,
			auto parseBody) {
			const auto name = functionName(lexer);
			const auto parameters = parameterList(lexer);
			auto body = parseBody(lexer); 
			return std::make_unique<FunctionalNode>(
				name,
				nameSpace,
				parameters,
				std::move(body),
				lexer.debug());
		}
	}

	// parses and returns a functional node
	std::unique_ptr<ast::Functional> functional(
		lex::Lexer & lexer,
		const ast::Namespace & nameSpace) {
		if(lexer.match(TT::FUNCTION)) {
			return functionalNode<ast::Function>(lexer, nameSpace, statement);
		}
		if(lexer.match(TT::ASM)) {
			return functionalNode<ast::Asm>(lexer, nameSpace, instructions);
		}
		return nullptr;
	}

	std::unique_ptr<ast::Lambda> lambda(lex::Lexer & lexer) {
		if(lexer.match(TT::FUNCTION)) {
			auto && captures = parse::captures(lexer);
			const auto parameters = parameterList(lexer);
			auto && body = statement(lexer); 
			auto && fx = std::make_unique<ast::Function>(
				"lambda",
				ast::Namespace{},
				parameters,
				std::move(body),
				lexer.debug());
			return std::make_unique<ast::Lambda>(
				std::move(fx),
				std::move(captures),
				lexer.debug()); 
		}
		return nullptr;
	}

}