#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include <iostream>

// The following functions are for parsing the head of function
// function foo(Type name, ...) -> RType

namespace ltn::c {
	namespace {
		using TT = Token::Type;



		// Returns a array of all parameters
		ast::Parameters parse_basic_parameters(Tokens & tokens) {
			
			if(match(TT::PAREN_R, tokens)) {
				return {};
			}

			ast::Parameters parameters{};
			while(true) {
				auto name = parse_parameter_name(tokens);
				auto type = parse_parameter_type(tokens);
				parameters.push_back(ast::Parameter{
					.name = name,
					.type = type,
				});
				if(match(TT::PAREN_R, tokens)) break;
				if(!match(TT::COMMA, tokens)) {
					throw CompilerError{
						"expected comma between parameters",
						location(tokens)};
				}
			}
			return parameters;
		}



		ast::Parameters parse_optional_parameters(Tokens & tokens) {
			if(match(TT::PAREN_L, tokens)) return parse_basic_parameters(tokens);
			return {};
		}


		ast::Parameters parse_mandatory_parameters(Tokens & tokens) {
			if(match(TT::PAREN_L, tokens)) return parse_basic_parameters(tokens);
			throw ltn::c::CompilerError{"missing (", location(tokens)};
		}



		// Returns a array of all parameters
		std::vector<std::unique_ptr<ast::Var>> parse_captures(Tokens & tokens) {
			if(!match(TT::BRACKET_L, tokens)) return {};

			std::vector<std::unique_ptr<ast::Var>> captures{};
			if(!match(TT::BRACKET_R, tokens)) {
				while(true) {
					const auto name = parse_variable_name(tokens);
					const auto & loc = location(tokens);
					auto var = std::make_unique<ast::Var>(name, ast::Namespace{}, loc);
					captures.push_back(std::move(var));
					if(match(TT::BRACKET_R, tokens)) break;
					if(!match(TT::COMMA, tokens)) {
						throw CompilerError{
							"expected comma between captures",
							location(tokens)};
					}
				}
			} 
			return captures;
		}



		std::string parse_build_in_key(Tokens & tokens) {
			if(!match(TT::AT, tokens)) {
				throw CompilerError{
					"Expected @ before build_in key",
					location(tokens) };
			}
			if(auto str = match(TT::INDENTIFIER, tokens)) {
				return str->str;
			}
			else {
				throw CompilerError{
					"Expected build_in key after @",
					location(tokens) };
			}
		}


		
		ast::stmt_ptr parse_body(Tokens & tokens) {
			if(match(TT::DRARROW, tokens)) {
				auto expr = parse_expression(tokens);
				const auto & loc = location(tokens);
				// match(TT::SEMICOLON, tokens);
				return std::make_unique<ast::Return>(std::move(expr), loc);
			}
			else {
				return parse_statement(tokens);
			}
		}



		std::unique_ptr<ast::Except> parse_except(Tokens & tokens) {
			if(match(TT::EXCEPT, tokens)) {
				auto params = parse_mandatory_parameters(tokens);
				if(params.size() != 1) {
					throw CompilerError{
						"Except only takes one error parameter",
						location(tokens)};
				}
				auto body = parse_body(tokens);
				return std::make_unique<ast::Except>(
					params[0].name,
					std::move(body),
					location(tokens));
			}
			else return nullptr;
		}



		// parses and returns a function node
		template<class FunctionalNode>
		std::unique_ptr<FunctionalNode> functional_node(
			Tokens & tokens,
			const ast::Namespace & namespaze,
			auto parse_body) {
			const auto name = parse_function_name(tokens);
			const auto parameters = parse_mandatory_parameters(tokens);
			bool c0nst = false;
			bool pr1vate = false;
			bool init = false;
			while(auto t = match(TT::INDENTIFIER, tokens)) {
				if(t->str == "const") {
					c0nst = true;
				}
				else if(t->str == "private") {
					pr1vate = true;
				}
				else if(t->str == "extern") {
					if(std::size(parameters) == 0 || std::size(parameters) == 1) {
						init = true;
					}
					else throw CompilerError {
						"An extern function must have 0 or 1 parameter(s)",
						t->location
					};
				}
				else {
					throw CompilerError{
						"Unknown function qualifier: " + t->str,
						t->location
					};
				}
			}			
			const auto return_type = parse_return_type(tokens);
			auto body = parse_body(tokens);
			auto fx = std::make_unique<FunctionalNode>(
				name,
				namespaze,
				parameters,
				std::move(body),
				return_type,
				location(tokens));
			fx->c0nst = c0nst;
			fx->pr1vate = pr1vate;
			fx->init = init;
			return fx;
		}
	}



	// parses and returns a functional node
	ast::func_ptr parse_functional(
		Tokens & tokens,
		const ast::Namespace & namespaze) {

		if(match(TT::FUNCTION, tokens)) {
			auto fx = functional_node<ast::Function>(
				tokens,
				namespaze,
				parse_body);
			if(!fx->c0nst) fx->except = parse_except(tokens);
			return fx;
		}
		if(match(TT::BUILD_IN, tokens)) {
			return functional_node<ast::BuildIn>(
				tokens,
				namespaze,
				parse_build_in_key);
		}
		return nullptr;
	}



	ast::expr_ptr parse_lambda(Tokens & tokens) {
		if(match(TT::LAMBDA, tokens)) {
			auto captures = parse_captures(tokens);
			const auto parameters = parse_optional_parameters(tokens);
			const auto return_type = parse_return_type(tokens);
			auto body = parse_body(tokens); 
			auto fx = std::make_unique<ast::Function>(
				"lambda" + std::to_string(*stx::unique{}), 
				ast::Namespace{},
				parameters,
				std::move(body),
				return_type,
				location(tokens));
			fx->except = parse_except(tokens);
			return std::make_unique<ast::Lambda>(
				std::move(fx),
				std::move(captures),
				location(tokens)); 
		}
		return nullptr;
	}
}