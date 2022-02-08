#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"
#include <iostream>
namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		using Functionals = std::vector<std::unique_ptr<ast::Functional>>;

		CompilerError anonymousNamespace(const lex::Lexer & lexer) {
			return CompilerError {
				"Expected namespace name. Anonymous not supported",
				lexer.location()};
		}

		CompilerError unknownDeclaration(const lex::Lexer & lexer) {
			return CompilerError(
				"Unknown declaration."
				"Exprected function, namespace or asm-function.",
				lexer.location());
		}

		CompilerError unclosedNamespace(const lex::Lexer & lexer) {
			return CompilerError {
				"Unclosed namespace. Expected }",
				lexer.location()};
		}

		CompilerError missingBraceR(const lex::Lexer & lexer) {
			return CompilerError {
				"Expected {",
				lexer.location()};
		}

		CompilerError extraBraceR(const lex::Lexer & lexer) {
			return CompilerError {
				"Extra {",
				lexer.location()};
		}

		// parses: namespace foo { ...
		std::optional<std::string> openNamespace(lex::Lexer & lexer) {
			if(lexer.match(TT::NAMESPACE)) {
				if(auto name = lexer.match(TT::INDENTIFIER)) {
					if(lexer.match(TT::BRACE_L)) {
						return name->str;
					}
					else throw missingBraceR(lexer);
				}
				else throw anonymousNamespace(lexer);
			}
			return {};
		}

		// }
		bool closeNamespace(
			lex::Lexer & lexer,
			ast::Namespace & nameSpace) {
			if(lexer.match(TT::BRACE_R)) {
				if(nameSpace.empty()) {
					throw extraBraceR(lexer);
				}
				return true;
			}
			return false;
		}
	}

	std::vector<std::unique_ptr<ast::Functional>> source(lex::Lexer & lexer) {
		Functionals functions;
		ast::Namespace nameSpace;
		ErrorAccu errors;
		while(!lexer.match(TT::___EOF___)) {
			try {
				if(auto ns = openNamespace(lexer)) {
					nameSpace.push_back(*ns);
				}
				else if(closeNamespace(lexer, nameSpace)) {
					nameSpace.pop_back();
				}
				else if(auto fx = parse::functional(lexer, nameSpace)) {
					functions.push_back(std::move(fx));
				}
				else throw unknownDeclaration(lexer);
			}
			catch(const CompilerError & error) {
				errors.push(error);
				lexer.sync();
			}
		}
		if(nameSpace.empty()) {
			errors.may_throw();
			return functions; 
		}
		else throw unclosedNamespace(lexer);
	}
}