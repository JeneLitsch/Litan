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
			
			auto global = std::make_unique<ast::Global>(
				name->location,
				name->str,
				std::move(namespaze)
			);

			if(match("extern", tokens)) {
				global->is_extern = true;
			}

			global->expr = match(TT::ASSIGN, tokens)
				? parse_expression(tokens)
				: nullptr;

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
	}



	ast::Program parse(Tokens & tokens, Reporter & reporter) {
		ast::Program source;
		const Namespace namespaze;

		stx::accu_stack<Namespace> namestack;

		while(!tokens.empty()) {
			if(match(TT::NAMESPACE, tokens)) {
				namestack.push(inner_namespace(tokens));
			}
			else if(match(TT::FUNCTION, tokens)) {
				auto fx = parse_function(tokens, namestack.top());
				source.functions.push_back(std::move(fx));
			}
			else if(match(TT::DEFINE, tokens)) {
				auto definition = parse_definition(tokens, namestack.top());
				source.definitions.push_back(std::move(definition));
			}
			else if(match(TT::ENUM, tokens)) {
				source.enums.push_back(parse_enumeration(tokens, namestack.top()));
			}
			else if(match(TT::VAR, tokens)) {
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
				if(!namestack.empty()) {
					throw unclosed_namespace(tokens);
				}
			}
			else {
				throw unknown_declaration(tokens);
			}
		}
		return source; 
	}
}