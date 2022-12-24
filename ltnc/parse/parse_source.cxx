#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include <iostream>
#include "stdxx/accu_stack.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;


		CompilerError anonymous_namespace(const Tokens & tokens) {
			return CompilerError {
				"Expected namespace name. Anonymous not supported",
				location(tokens)};
		}



		CompilerError unknown_declaration(const Tokens & tokens) {
			return CompilerError(
				"Unknown declaration."
				"Exprected function, namespace or asm-function.",
				location(tokens));
		}



		CompilerError unclosed_namespace(const Tokens & tokens) {
			return CompilerError {
				"Unclosed namespace. Expected }",
				location(tokens)};
		}



		CompilerError missing_brace_l(const Tokens & tokens) {
			return CompilerError {
				"Expected {",
				location(tokens)};
		}



		CompilerError extra_brace_r(const Tokens & tokens) {
			return CompilerError {
				"Extra }",
				location(tokens)};
		}



		ast::glob_ptr parse_global_decl(
			Tokens & tokens,
			const Namespace & namespaze) {
			
			const auto name = match(TT::INDENTIFIER, tokens);

			if(!name) throw CompilerError {
				"Expected name after global declaration",
			};
			
			const auto type = parse_var_type(tokens);

			auto global = stx::make_unique<ast::Global>(
				name->location,
				name->str,
				namespaze,
				type
			);

			if(match(TT::ASSIGN, tokens)) {
				global->expr = parse_expression(tokens);
			}

			semicolon(tokens);
			return global;
		}



		Namespace inner_namespace(Tokens & tokens) {
			Namespace namespaze;
			do {
				if(auto t = match(TT::INDENTIFIER, tokens)) {
					namespaze.push_back(t->str);
				}
				else throw anonymous_namespace(tokens);
			} while(match(TT::COLONx2, tokens));

			if(match(TT::BRACE_L, tokens)) return namespaze;
			else throw missing_brace_l(tokens);
		}



		void add_to_source(ast::func_ptr && fx, ast::Program & source) {
			source.functions.push_back(std::move(fx));
		}



		void add_to_source(ast::ftmp_ptr && fx, ast::Program & source) {
			source.function_templates.push_back(std::move(fx));
		}
	}




	ast::Program parse(Tokens & tokens, Reporter & reporter) {
		ast::Program source;

		stx::accu_stack<Namespace> namestack;

		while(!tokens.empty()) {
			try {
				if(match(TT::NAMESPACE, tokens)) {
					namestack.push(inner_namespace(tokens));
				}
				else if(auto fx = parse_functional(tokens, namestack.top())) {
					std::visit([&] (auto & node) {
						add_to_source(std::move(node), source);
					}, *fx);
				}
				else if(auto definition = parse_definition(tokens, namestack.top())) {
					source.definitions.push_back(std::move(definition));
				}
				else if(auto preset = parse_preset(tokens, namestack.top())) {
					source.presets.push_back(std::move(preset));
				}
				else if(auto overload = parse_overload(tokens, namestack.top())) {
					std::cout << overload->namespaze.to_string() << overload->name << "\n";
				}
				else if(match(TT::ENUM, tokens)) {
					source.enums.push_back(parse_enumeration(tokens, namestack.top()));
				}
				else if(match(TT::GLOBAL, tokens)) {
					source.globals.push_back(parse_global_decl(tokens, namestack.top()));
				}
				else if(match(TT::BRACE_R, tokens)) {
					if(namestack.empty()) {
						throw extra_brace_r(tokens);
					}
					else {
						namestack.pop();
					}
				}
				else if(match(TT::___EOF___, tokens)) {
					if(namestack.empty()) {
						// Nothing
					}
					else {
						throw unclosed_namespace(tokens);
					}
				}
				else {
					throw unknown_declaration(tokens);
				}
			}
			catch(const CompilerError & error) {
				reporter << error;
				while(tokens.front().type != TT::___EOF___) tokens.pop();
				namestack = {};
			}
		}

		return source; 
	}
}