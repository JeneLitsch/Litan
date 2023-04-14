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
					throw CompilerError {
						"expected comma between parameters",
						location(tokens)
					};
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



		std::vector<std::unique_ptr<ast::Var>> parse_captures(Tokens & tokens) {
			if(!match(TT::BRACKET_L, tokens)) return {};

			std::vector<std::unique_ptr<ast::Var>> captures{};
			if(!match(TT::BRACKET_R, tokens)) {
				while(true) {
					const auto name = parse_variable_name(tokens);
					const auto & loc = location(tokens);
					auto var = stx::make_unique<ast::Var>(name, Namespace{}, loc);
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
			if(!match(TT::AT, tokens)) {
				throw CompilerError {
					"Expected @ before build_in key",
					location(tokens)
				};
			}
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
			return stx::make_unique<ast::Return>(std::move(expr), i->location);
		}



		ast::stmt_ptr parse_special_body(Tokens & tokens, std::uint64_t arity) {
			if(auto t = match(TT::INDENTIFIER, tokens)) {
				if(t->str == "dynamic") {
					return parse_dynamic_body(tokens, arity);
				}
				else throw CompilerError {
					"Unknown function type " + t->str
				};
			}
			else throw CompilerError {
				"Expected function type after ="
			};
		}


		
		ast::stmt_ptr parse_body(Tokens & tokens, std::uint64_t arity) {
			if(match(TT::ASSIGN, tokens)) {
				return parse_special_body(tokens, arity);
			}
			else if(match(TT::DRARROW, tokens)) {
				auto expr = parse_expression(tokens);
				const auto & loc = location(tokens);
				return stx::make_unique<ast::Return>(std::move(expr), loc);
			}
			else {
				return parse_statement(tokens);
			}
		}



		std::unique_ptr<ast::Except> parse_except(Tokens & tokens) {
			if(match(TT::EXCEPT, tokens)) {
				auto params = parse_mandatory_parameters(tokens);
				if(params.size() != 1) {
					throw CompilerError {
						"Except only takes one error parameter",
						location(tokens)
					};
				}
				auto body = parse_body(tokens, 1);
				return stx::make_unique<ast::Except>(
					params[0].name,
					std::move(body),
					location(tokens)
				);
			}
			else return nullptr;
		}



		template<class FunctionalNode>
		std::unique_ptr<FunctionalNode> functional_node(
			Tokens & tokens,
			const Namespace & namespaze,
			auto parse_body) {
			const auto name = parse_function_name(tokens);
			const auto parameters = parse_mandatory_parameters(tokens);
			bool is_const = false;
			bool is_private = false;
			bool is_extern = false;
			while(auto t = match(TT::INDENTIFIER, tokens)) {
				if(t->str == "const") {
					is_const = true;
				}
				else if(t->str == "private") {
					is_private = true;
				}
				else if(t->str == "extern") {
					is_extern = true;
				}
				else {
					throw CompilerError {
						"Unknown function qualifier: " + t->str,
						t->location
					};
				}
			}			
			const auto return_type = parse_return_type(tokens);
			auto body = parse_body(tokens, std::size(parameters));
			auto fx = stx::make_unique<FunctionalNode>(
				name,
				namespaze,
				parameters,
				std::move(body),
				return_type,
				location(tokens));
			fx->is_const = is_const;
			fx->is_private = is_private;
			fx->is_extern = is_extern;
			return fx;
		}



		std::vector<std::string> parse_template_parameters(Tokens & tokens) {
			std::vector<std::string> template_parameters;
			if(auto begin = match(TT::SMALLER, tokens)) {
				do {
					auto t = match(TT::INDENTIFIER, tokens);
					if (!t) throw CompilerError{
						"Expected template parameter",
						begin->location
					};
					template_parameters.push_back(t->str);
				} while(match(TT::COMMA, tokens));
				if (!match(TT::BIGGER, tokens)) throw CompilerError{
					"Expected > after template parameters",
					begin->location
				};
			}
			return template_parameters;
		}
	}



	// parses and returns a functional node
	std::optional<std::variant<ast::func_ptr, ast::ftmp_ptr>> parse_functional(
		Tokens & tokens,
		const Namespace & namespaze) {

		if(auto function = match(TT::FUNCTION, tokens)) {
			const auto template_parameters = parse_template_parameters(tokens);
			auto fx = functional_node<ast::Function>(
				tokens,
				namespaze,
				parse_body);
			if(!fx->is_const) fx->except = parse_except(tokens);
			if(template_parameters.empty()) {
				return fx;
			}
			return stx::make_unique<ast::FunctionTemplate>(
				std::move(fx),
				std::move(template_parameters),
				function->location
			);
		}
		if(auto function = match(TT::BUILD_IN, tokens)) {
			const auto template_parameters = parse_template_parameters(tokens);
			auto fx = functional_node<ast::BuildIn>(
				tokens,
				namespaze,
				parse_build_in_key);
			if(template_parameters.empty()) {
				return fx;
			}
			return stx::make_unique<ast::FunctionTemplate>(
				std::move(fx),
				std::move(template_parameters),
				function->location
			);
		}
		return std::nullopt;
	}



	ast::expr_ptr parse_lambda(Tokens & tokens) {
		if(match(TT::LAMBDA, tokens)) {
			auto captures = parse_captures(tokens);
			const auto parameters = parse_optional_parameters(tokens);
			const auto return_type = parse_return_type(tokens);
			auto body = parse_body(tokens, std::size(parameters)); 
			auto fx = stx::make_unique<ast::Function>(
				"lambda" + std::to_string(*stx::unique{}), 
				Namespace{},
				parameters,
				std::move(body),
				return_type,
				location(tokens));
			fx->except = parse_except(tokens);
			return stx::make_unique<ast::Lambda>(
				std::move(fx),
				std::move(captures),
				location(tokens)); 
		}
		return nullptr;
	}
}