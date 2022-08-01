#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include <iostream>
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



		// parses: namespace foo { ...
		std::optional<std::string> open_namespace(Tokens & tokens) {
			if(match(TT::NAMESPACE, tokens)) {
				if(auto name = match(TT::INDENTIFIER, tokens)) {
					if(match(TT::BRACE_L, tokens)) {
						return name->str;
					}
					else throw missing_brace_l(tokens);
				}
				else throw anonymous_namespace(tokens);
			}
			return {};
		}



		// }
		bool close_namespace(
			Tokens & tokens,
			ast::Namespace & namespaze) {
			if(match(TT::BRACE_R, tokens)) {
				if(namespaze.empty()) {
					throw extra_brace_r(tokens);
				}
				return true;
			}
			return false;
		}

		
		
		ast::glob_ptr parse_global_decl(
			Tokens & tokens,
			const ast::Namespace & namespaze) {
			
			const auto name = match(TT::INDENTIFIER, tokens);

			if(!name) throw CompilerError {
				"Expected name after global declaration",
			};

			auto global = std::make_unique<ast::Global>(
				name->location,
				name->str,
				namespaze);

			if(match(TT::ASSIGN, tokens)) {
				global->expr = parse_expression(tokens);
			}

			semicolon(tokens);
			return global;
		}



		void parse_namespace(Tokens &, ast::Source &, const ast::Namespace &);

		bool parse_decl(Tokens & tokens, ast::Source & source, const ast::Namespace & ns) {
			if(match(TT::NAMESPACE, tokens)) {
				parse_namespace(tokens, source, ns);
				return true;
			}
			else if(auto fx = parse_functional(tokens, ns)) {
				source.functions.push_back(std::move(fx));
				return true;
			}
			else if(auto definition = parse_definition(tokens, ns)) {
				source.definitions.push_back(std::move(definition));
				return true;
			}
			else if(auto preset = parse_preset(tokens, ns)) {
				source.presets.push_back(std::move(preset));
				return true;
			}
			else if(match(TT::ENUM, tokens)) {
				source.enums.push_back(parse_enumeration(tokens, ns));
				return true;
			}
			else if(match(TT::GLOBAL, tokens)) {
				source.globals.push_back(parse_global_decl(tokens, ns));
				return true;
			}
			else return false;
		}



		void parse_namespace(Tokens & tokens, ast::Source & source, const ast::Namespace & outer) {
			ast::Namespace namespaze = outer;
			if(auto t = match(TT::INDENTIFIER, tokens)) {
				namespaze.push_back(t->str);
			}
			else throw anonymous_namespace(tokens);

			if(!match(TT::BRACE_L, tokens)) throw missing_brace_l(tokens);

			while(!match(TT::___EOF___, tokens)) {
				if(parse_decl(tokens, source, namespaze)) {
					// Nothing
				}
				else if(match(TT::BRACE_R, tokens)) {
					return;
				}
				else if(match(TT::___EOSRC___, tokens)) {
					throw unclosed_namespace(tokens);
				}
				else {
					throw unknown_declaration(tokens);
				}
			}
		}
	}



	ast::srce_ptr parse_source(Tokens & tokens) {
		auto source = std::make_unique<ast::Source>();
		const ast::Namespace namespaze;
		Reporter reporter;
		while(!match(TT::___EOF___, tokens)) {
			try {
				if(parse_decl(tokens, *source, namespaze)) {
					// Nothing
				}
				else if(match(TT::BRACE_R, tokens)) {
					throw extra_brace_r(tokens);
				}
				else if(match(TT::___EOSRC___, tokens)) {
					// Nothing
				}
				else throw unknown_declaration(tokens);
			}
			catch(const CompilerError & error) {
				reporter << error;
				sync(tokens);
			}
		}
		reporter.may_throw();
		return source; 
	}
}