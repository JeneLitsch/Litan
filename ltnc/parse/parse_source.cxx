#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include <iostream>
namespace ltn::c {
	namespace {
		using TT = ltn::c::lex::Token::Type;


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
	}



	ast::srce_ptr parse_source(Tokens & tokens) {
		auto source = std::make_unique<ast::Source>();
		auto & functions = source->functions;
		auto & globals = source->globals;
		auto & presets = source->presets;
		auto & enums = source->enums;
		ast::Namespace namespaze;
		Reporter reporter;
		while(!match(TT::___EOF___, tokens)) {
			try {
				if(auto ns = open_namespace(tokens)) {
					namespaze.push_back(*ns);
				}
				else if(close_namespace(tokens, namespaze)) {
					namespaze.pop_back();
				}
				else if(auto fx = parse_functional(tokens, namespaze)) {
					functions.push_back(std::move(fx));
				}
				else if(auto global = parse_definition(tokens, namespaze)) {
					globals.push_back(std::move(global));
				}
				else if(auto preset = parse_preset(tokens, namespaze)) {
					presets.push_back(std::move(preset));
				}
				else if(match(TT::ENUM, tokens)) {
					auto e = parse_enumeration(tokens, namespaze);
					enums.push_back(std::move(e));
				}			
				else if(match(TT::___EOSRC___, tokens)) {
					throw unclosed_namespace(tokens);	
				}
				else throw unknown_declaration(tokens);
			
				if(namespaze.empty()) match(TT::___EOSRC___, tokens);
			}
			catch(const CompilerError & error) {
				reporter << error;
				sync(tokens);
			}
		}
		if(!namespaze.empty()) {
			throw unclosed_namespace(tokens);
		}
		reporter.may_throw();
		return source; 
	}
}