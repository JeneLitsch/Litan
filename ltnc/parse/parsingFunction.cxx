#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"
#include <iostream>

// The following functions are for parsing the head of function
// function foo(Type name, ...) -> RType

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;

		// Returns a array of all parameters
		ast::Parameters parameter_list(lex::Lexer & lexer) {
			if(!lexer.match(TT::PAREN_L)) {
				throw ltn::c::CompilerError{"missing (", lexer.location()};
			}
			
			ast::Parameters parameters{};
			if(!lexer.match(TT::PAREN_R)) {
				while(true) {
					parameters.push_back(parse::parameter_name(lexer));
					if(lexer.match(TT::PAREN_R)) break;
					if(!lexer.match(TT::COMMA)) {
						throw CompilerError{
							"expected comma between parameters",
							lexer.location()};
					}
				}
			} 
			return parameters;
		}

		ast::Parameters optional_parameters(lex::Lexer & lexer) {
			if(lexer.check(TT::PAREN_L)) return parameter_list(lexer);
			return {};
		}

		// Returns a array of all parameters
		std::vector<std::unique_ptr<ast::Var>> captures(lex::Lexer & lexer) {
			if(!lexer.match(TT::BRACKET_L)) return {};

			std::vector<std::unique_ptr<ast::Var>> captures{};
			if(!lexer.match(TT::BRACKET_R)) {
				while(true) {
					const auto name = parse::variable_name(lexer);
					const auto & location = lexer.location();
					auto var = std::make_unique<ast::Var>(name, location);
					captures.push_back(std::move(var));
					if(lexer.match(TT::BRACKET_R)) break;
					if(!lexer.match(TT::COMMA)) {
						throw CompilerError{
							"expected comma between captures",
							lexer.location()};
					}
				}
			} 
			return captures;
		}

		std::string build_in_key(lex::Lexer & lexer) {
			if(!lexer.match(TT::AT)) {
				throw CompilerError{
					"Expected @ before build_in key",
					lexer.location() };
			}
			if(auto str = lexer.match(TT::INDENTIFIER)) {
				return str->str;
			}
			else {
				throw CompilerError{
					"Expected build_in key after @",
					lexer.location() };
			}
		}


		ast::stmt_ptr body(lex::Lexer & lexer) {
			if(lexer.match(TT::DRARROW)) {
				auto expr = expression(lexer);
				const auto & location = lexer.location();
				return std::make_unique<ast::Return>(std::move(expr), location);
			}
			else {
				return statement(lexer);
			}
		}

		std::unique_ptr<ast::Except> except(lex::Lexer & lexer) {
			if(lexer.match(TT::EXCEPT)) {
				auto params = parameter_list(lexer);
				if(params.size() != 1) {
					throw CompilerError{
						"Except only takes one error parameter",
						lexer.location()};
				}
				auto body = parse::body(lexer);
				return std::make_unique<ast::Except>(
					params[0],
					std::move(body),
					lexer.location());
			}
			else return nullptr;
		}


		// parses and returns a function node
		template<class FunctionalNode>
		std::unique_ptr<FunctionalNode> functional_node(
			lex::Lexer & lexer,
			const ast::Namespace & namespaze,
			auto parse_body) {
			const auto name = function_name(lexer);
			const auto parameters = parameter_list(lexer);
			auto body = parse_body(lexer);
			return std::make_unique<FunctionalNode>(
				name,
				namespaze,
				parameters,
				std::move(body),
				lexer.location());
		}
	}


	// parses and returns a functional node
	ast::func_ptr functional(
		lex::Lexer & lexer,
		const ast::Namespace & namespaze) {

		if(lexer.match(TT::FUNCTION)) {
			auto fx = functional_node<ast::Function>(
				lexer,
				namespaze,
				parse::body);
			fx->except = parse::except(lexer);
			return fx;
		}
		if(lexer.match(TT::BUILD_IN)) {
			return functional_node<ast::BuildIn>(
				lexer,
				namespaze,
				build_in_key);
		}
		return nullptr;
	}

	ast::expr_ptr lambda(lex::Lexer & lexer) {
		if(lexer.match(TT::LAMBDA)) {
			auto captures = parse::captures(lexer);
			const auto parameters = optional_parameters(lexer);
			auto body = parse::body(lexer); 
			auto fx = std::make_unique<ast::Function>(
				"lambda", 
				ast::Namespace{},
				parameters,
				std::move(body),
				lexer.location());
			fx->except = parse::except(lexer);
			return std::make_unique<ast::Lambda>(
				std::move(fx),
				std::move(captures),
				lexer.location()); 
		}
		return nullptr;
	}
}