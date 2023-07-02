#include "parse.hxx"
#include "stdxx/iife.hxx"
#include "ltnc/CompilerError.hxx"
#include <iostream>

// The following functions are for parsing the head of function
// function foo(Type name, ...) -> RType

namespace ltn::c {
	namespace {
		using TT = Token::Type;

		struct Qualifiers {
			bool is_const = false;
			bool is_extern = false;
			bool is_private = false;
		};



		// Returns a array of all parameters
		ast::Parameters parse_parameters_variadic(Tokens & tokens) {
			
			if(match(TT::PAREN_R, tokens)) {
				return {};
			}

			ast::Parameters parameters{};
			while(true) {
				auto name = parse_parameter_name(tokens);
				if(match(TT::ELLIPSIS, tokens)) {
					parameters.variadic = ast::Parameter {
						.name = name
					};
					if(!match(TT::PAREN_R, tokens)) throw CompilerError {
						"Variadic parameter must the last one",
						location(tokens)
					};
					return parameters;
				}
				else {
					parameters.simple.push_back(ast::Parameter{
						.name = std::move(name),
					});
					if(match(TT::PAREN_R, tokens)) return parameters;
					if(!match(TT::COMMA, tokens)) throw CompilerError {
						"expected comma between parameters",
						location(tokens)
					};
				}
			}
		}



		// Returns a array of all parameters
		ast::Parameters parse_parameters(Tokens & tokens) {
			
			if(match(TT::PAREN_R, tokens)) {
				return {};
			}

			ast::Parameters parameters{};
			while(true) {
				auto name = parse_parameter_name(tokens);
				parameters.simple.push_back(ast::Parameter{
					.name = std::move(name),
				});
				if(match(TT::PAREN_R, tokens)) return parameters;
				if(!match(TT::COMMA, tokens)) throw CompilerError {
					"expected comma between parameters",
					location(tokens)
				};
			}
		}



		ast::Parameters parse_lambda_parameters(Tokens & tokens) {
			if(match(TT::PAREN_L, tokens)) return parse_parameters_variadic(tokens);
			return {};
		}

		
		ast::Parameters parse_except_parameters(Tokens & tokens) {
			if(match(TT::PAREN_L, tokens)) return parse_parameters(tokens);
			throw ltn::c::CompilerError{"missing (", location(tokens)};
		}


		ast::Parameters parse_function_parameters(Tokens & tokens) {
			if(match(TT::PAREN_L, tokens)) return parse_parameters_variadic(tokens);
			throw ltn::c::CompilerError{"missing (", location(tokens)};
		}



		std::vector<std::unique_ptr<ast::Var>> parse_captures(Tokens & tokens) {
			if(!match(TT::BRACKET_L, tokens)) return {};

			std::vector<std::unique_ptr<ast::Var>> captures{};
			if(!match(TT::BRACKET_R, tokens)) {
				while(true) {
					const auto name = parse_variable_name(tokens);
					const auto & loc = location(tokens);
					auto var = std::make_unique<ast::Var>(name, Namespace{}, loc);
					captures.push_back(std::move(var));
					if(match(TT::BRACKET_R, tokens)) break;
					if(!match(TT::COMMA, tokens)) {
						throw CompilerError {
							"expected comma between captures",
							location(tokens)
						};
					}
				}
			} 
			return captures;
		}



		std::string parse_build_in_key(Tokens & tokens, [[maybe_unused]] std::uint64_t arity) {
			if(auto str = match(TT::INDENTIFIER, tokens)) {
				return str->str;
			}
			else {
				throw CompilerError {
					"Expected build_in key after @",
					location(tokens)
				};
			}
		}



		ast::stmt_ptr parse_dynamic_body(Tokens & tokens, std::uint64_t arity) {
			if(!match(TT::PAREN_L, tokens)) throw CompilerError {
				"Expected ("
			};
			auto i = match(TT::INTEGER_HEX, tokens);
			if(!i)  throw CompilerError {
				"Unsupported dynamic link code " + i->str, i->location
			};
			if(!match(TT::PAREN_R, tokens)) throw CompilerError {
				"Expected )"
			};
			std::stringstream iss{i->str};
			std::uint64_t address;
			iss >> std::hex >> address;
			auto expr = std::make_unique<ast::ForwardDynamicCall>(
				address, arity, i->location
			);
			return std::make_unique<ast::Return>(std::move(expr), i->location);
		}




		ast::stmt_ptr parse_build_in_body(Tokens & tokens, std::uint64_t arity, const Token & begin) {
			if(!match(TT::PAREN_L, tokens)) throw CompilerError {
				"Expected ("
			};
			
			auto key = parse_build_in_key(tokens, arity);

			if(!match(TT::PAREN_R, tokens)) throw CompilerError {
				"Expected )"
			};

			auto expr = std::make_unique<ast::RunBuildIn>(std::move(key), begin.location);
			return std::make_unique<ast::Return>(std::move(expr), begin.location);
		}


		
		ast::stmt_ptr parse_body(Tokens & tokens, std::uint64_t arity) {
			if(auto begin = match(TT::DRARROW, tokens)) {
				if(match("dynamic", tokens)) {
					return parse_dynamic_body(tokens, arity);
				}
				if(match(TT::BUILD_IN, tokens)) {
					return parse_build_in_body(tokens, arity, *begin);
				}
				auto expr = parse_expression(tokens);
				const auto & loc = location(tokens);
				return std::make_unique<ast::Return>(std::move(expr), loc);
			}
			else {
				return parse_statement(tokens);
			}
		}



		std::unique_ptr<ast::Except> parse_except(Tokens & tokens) {
			if(match(TT::EXCEPT, tokens)) {
				auto params = parse_except_parameters(tokens);
				if(params.simple.size() != 1) {
					throw CompilerError {
						"Except only takes one error parameter",
						location(tokens)
					};
				}
				auto body = parse_body(tokens, 1);
				return std::make_unique<ast::Except>(
					params.simple[0].name,
					std::move(body),
					location(tokens)
				);
			}
			else return nullptr;
		}



		Qualifiers parse_qualifiers(Tokens & tokens) {
			Qualifiers q;
			while(auto t = match(TT::INDENTIFIER, tokens)) {
				if(t->str == "const") {
					q.is_const = true;
				}
				else if(t->str == "private") {
					q.is_private = true;
				}
				else if(t->str == "extern") {
					q.is_extern = true;
				}
				else {
					throw CompilerError {
						"Unknown function qualifier: " + t->str,
						t->location
					};
				}
			}
			return q;
		}



		template<class FunctionalNode>
		std::unique_ptr<FunctionalNode> functional_node(
			Tokens & tokens,
			const Namespace & namespaze,
			auto parse_body) {
			auto name = parse_function_name(tokens);
			auto parameters = parse_function_parameters(tokens);

			Qualifiers qualifiers = parse_qualifiers(tokens); 
			auto body = parse_body(tokens, std::size(parameters.simple));
			auto fx = std::make_unique<FunctionalNode>(
				std::move(name),
				std::move(namespaze),
				std::move(parameters),
				std::move(body),
				location(tokens)
			);
			fx->is_const = qualifiers.is_const;
			fx->is_private = qualifiers.is_private;
			fx->is_extern = qualifiers.is_extern;
			return fx;
		}
	}



	// parses and returns a functional node
	std::optional<ast::func_ptr> parse_functional(
		Tokens & tokens,
		const Namespace & namespaze) {

		if(auto function = match(TT::FUNCTION, tokens)) {
			auto fx = functional_node<ast::Function>(
				tokens,
				namespaze,
				parse_body);
			if(!fx->is_const) fx->except = parse_except(tokens);
			return fx;
		}
		if(auto function = match(TT::BUILD_IN, tokens)) {
			auto fx = functional_node<ast::BuildIn>(
				tokens,
				namespaze,
				[] (Tokens & tokens, std::uint64_t arity) {
					if(!match(TT::AT, tokens)) {
						throw CompilerError {
							"Expected @ before build_in key",
							location(tokens)
						};
					}
					return parse_build_in_key(tokens, arity);
				}
			);
			return fx;
		}
		return std::nullopt;
	}



	ast::expr_ptr parse_lambda(Tokens & tokens) {
		if(match(TT::LAMBDA, tokens)) {
			auto captures = parse_captures(tokens);
			auto parameters = parse_lambda_parameters(tokens);
			Qualifiers qualifiers = parse_qualifiers(tokens);
			auto body = parse_body(tokens, std::size(parameters.simple)); 
			auto fx = std::make_unique<ast::Function>(
				"lambda" + std::to_string(*stx::unique{}), 
				Namespace{},
				std::move(parameters),
				std::move(body),
				location(tokens));
			fx->except = parse_except(tokens);
			fx->is_const = qualifiers.is_const;
			if(qualifiers.is_private) throw CompilerError { "Lambda cannot be private", location(tokens)};
			if(qualifiers.is_extern) throw CompilerError {"Lambda cannot be extern", location(tokens)};
			return std::make_unique<ast::Lambda>(
				std::move(fx),
				std::move(captures),
				location(tokens)); 
		}
		return nullptr;
	}
}