#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include <iostream>
#include "stdxx/accu_stack.hxx"
#include "tokenize.hxx"
#include "ltnc/source/FileSource.hxx"

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
			
			auto global = std::make_unique<ast::decl::Global>(
				name->location,
				name->str,
				std::move(namespaze)
			);

			while(auto qualifier = match(TT::INDENTIFIER, tokens)) {
				if(qualifier->str == "extern") {
					global->is_extern = true;
				}

				else if(qualifier->str == "private") {
					global->is_private = true;
				}

				else {
					throw CompilerError {
						"Unknown variable qualifier: " + qualifier->str,
						qualifier->location
					};
				}
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



		FileSource parse_import(const Source & includer, const Token & start, Tokens & tokens) {
			const std::filesystem::path source_path = includer.get_full_name(); 
			const std::filesystem::path parent_path = source_path.parent_path();
			if(auto path = match(TT::STRING, tokens)) {
				const std::filesystem::path dependecy_path = parent_path / path->str;
				return FileSource{dependecy_path / "_module_.ltn"};
			}
			else {
				throw CompilerError {"Import directive requires file path as quoted string", start.location};
			}
		}



		FileSource parse_include(const Source & includer, const Token & start, Tokens & tokens) {
			const std::filesystem::path source_path = includer.get_full_name(); 
			const std::filesystem::path parent_path = source_path.parent_path();
			if(auto path = match(TT::STRING, tokens)) {
				const std::filesystem::path dependecy_path = parent_path / path->str;
				return FileSource{dependecy_path};
			}
			else {
				throw CompilerError {"Include directive requires file path as quoted string", start.location};
			}
		}



		void process_source(
			const Source & source,
			ast::Program & ast,
			std::queue<Source> & pending_sources) {

			// std::cout << "[Source] " << std::filesystem::path{source.get_full_name()} << "\n";

			Tokens tokens = tokenize(source);
			stx::accu_stack<Namespace> namestack;

			while(!tokens.empty()) {
				if(match(TT::NAMESPACE, tokens)) {
					namestack.push(inner_namespace(tokens));
				}
				else if(match(TT::FUNCTION, tokens)) {
					auto fx = parse_function(tokens, namestack.top());
					ast.functions.push_back(std::move(fx));
				}
				else if(match(TT::DEFINE, tokens)) {
					auto definition = parse_definition(tokens, namestack.top());
					ast.definitions.push_back(std::move(definition));
				}
				else if(match(TT::ENUM, tokens)) {
					ast.enums.push_back(parse_enumeration(tokens, namestack.top()));
				}
				else if(match(TT::VAR, tokens)) {
					ast.globals.push_back(parse_global_decl(tokens, namestack.top()));
				}
				else if(auto start = match(TT::HASH_INCLUDE, tokens)) {
					pending_sources.push(parse_include(source, *start, tokens));
				}
				else if(auto start = match(TT::HASH_IMPORT, tokens)) {
					pending_sources.push(parse_import(source, *start, tokens));
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
		}
	}


	ast::Program parse(const std::vector<Source> & sources) {
		ast::Program ast;
		std::vector<std::filesystem::path> known_sources;
		std::queue<Source> pending_sources;

		for(const auto & source : sources) {
			const std::filesystem::path path = source.get_full_name(); 
			process_source(source, ast, pending_sources);
			known_sources.push_back(path);
		}

		while(!std::empty(pending_sources)) {
			const std::filesystem::path path = pending_sources.front().get_full_name(); 
			const bool new_source = std::none_of(std::begin(known_sources), std::end(known_sources), [&] (auto & s) {
				return std::filesystem::equivalent(s, path);
			}); 
			if(new_source) {
				process_source(pending_sources.front(), ast, pending_sources);
				known_sources.push_back(path);
			}
			pending_sources.pop();
		}

		return ast;
	}
}