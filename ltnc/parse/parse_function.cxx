#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include <iostream>

// The following functions are for parsing the head of function
// function foo(Type name, ...) -> RType

namespace ltn::c {
	namespace {
		using TT = ltn::c::lex::Token::Type;



		// Returns a array of all parameters
		ast::Parameters parse_basic_parameters(lex::Lexer & lexer) {
			
			if(lexer.match(TT::PAREN_R)) {
				return {};
			}

			ast::Parameters parameters{};
			while(true) {
				parameters.push_back(parse_parameter_name(lexer));
				if(lexer.match(TT::PAREN_R)) break;
				if(!lexer.match(TT::COMMA)) {
					throw CompilerError{
						"expected comma between parameters",
						lexer.location()};
				}
			}
			return parameters;
		}



		ast::Parameters parse_optional_parameters(lex::Lexer & lexer) {
			if(lexer.match(TT::PAREN_L)) return parse_basic_parameters(lexer);
			return {};
		}


		ast::Parameters parse_mandatory_parameters(lex::Lexer & lexer) {
			if(lexer.match(TT::PAREN_L)) return parse_basic_parameters(lexer);
			throw ltn::c::CompilerError{"missing (", lexer.location()};
		}



		// Returns a array of all parameters
		std::vector<std::unique_ptr<ast::Var>> parse_captures(lex::Lexer & lexer) {
			if(!lexer.match(TT::BRACKET_L)) return {};

			std::vector<std::unique_ptr<ast::Var>> captures{};
			if(!lexer.match(TT::BRACKET_R)) {
				while(true) {
					const auto name = parse_variable_name(lexer);
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



		std::string parse_build_in_key(lex::Lexer & lexer) {
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



		ast::stmt_ptr parse_body(lex::Lexer & lexer) {
			if(lexer.match(TT::DRARROW)) {
				auto expr = parse_expression(lexer);
				const auto & location = lexer.location();
				return std::make_unique<ast::Return>(std::move(expr), location);
			}
			else {
				return parse_statement(lexer);
			}
		}



		std::unique_ptr<ast::Except> parse_except(lex::Lexer & lexer) {
			if(lexer.match(TT::EXCEPT)) {
				auto params = parse_mandatory_parameters(lexer);
				if(params.size() != 1) {
					throw CompilerError{
						"Except only takes one error parameter",
						lexer.location()};
				}
				auto body = parse_body(lexer);
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
			const auto name = parse_function_name(lexer);
			const auto parameters = parse_mandatory_parameters(lexer);
			bool c0nst = false;
			bool pr1vate = false;
			while(auto t = lexer.match(TT::INDENTIFIER)) {
				if(t->str == "const") {
					c0nst = true;
				}
				else if(t->str == "private") {
					pr1vate = true;
				}
				else {
					throw CompilerError{
						"Unknown function qualifier: " + t->str,
						t->location
					};
				}
			}			
			auto body = parse_body(lexer);
			auto fx = std::make_unique<FunctionalNode>(
				name,
				namespaze,
				parameters,
				std::move(body),
				lexer.location());
			fx->c0nst = c0nst;
			fx->pr1vate = pr1vate;
			return fx;
		}
	}



	// parses and returns a functional node
	ast::func_ptr parse_functional(
		lex::Lexer & lexer,
		const ast::Namespace & namespaze) {

		if(lexer.match(TT::FUNCTION)) {
			auto fx = functional_node<ast::Function>(
				lexer,
				namespaze,
				parse_body);
			if(!fx->c0nst) fx->except = parse_except(lexer);
			return fx;
		}
		if(lexer.match(TT::BUILD_IN)) {
			return functional_node<ast::BuildIn>(
				lexer,
				namespaze,
				parse_build_in_key);
		}
		return nullptr;
	}



	ast::expr_ptr parse_lambda(lex::Lexer & lexer) {
		if(lexer.match(TT::LAMBDA)) {
			auto captures = parse_captures(lexer);
			const auto parameters = parse_optional_parameters(lexer);
			auto body = parse_body(lexer); 
			auto fx = std::make_unique<ast::Function>(
				"lambda" + std::to_string(*stx::unique{}), 
				ast::Namespace{},
				parameters,
				std::move(body),
				lexer.location());
			fx->except = parse_except(lexer);
			return std::make_unique<ast::Lambda>(
				std::move(fx),
				std::move(captures),
				lexer.location()); 
		}
		return nullptr;
	}
}