#include "parse.hxx"
#include "litan_compiler/CompilerError.hxx"
#include <iostream>
#include "stdxx/accu_stack.hxx"
#include "tokenize.hxx"
#include "litan_compiler/source/FileSource.hxx"
#include "litan_compiler/source/ModuleSource.hxx"

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



		struct Options {
			std::map<std::string, std::filesystem::path> include_paths;
		};




		Source parse_import(const Source & includer, const Token & start, Tokens & tokens) {
			const std::filesystem::path source_path = includer.get_full_name(); 
			const std::filesystem::path parent_path = source_path.parent_path();
			if(auto path = match(TT::STRING, tokens)) {
				const std::filesystem::path dependecy_path = parent_path / path->str;
				if(std::filesystem::is_directory(dependecy_path)) {
					return ModuleSource{dependecy_path};
				}
				else if(std::filesystem::is_regular_file(dependecy_path)) {
					return FileSource{dependecy_path};
				}
				else {
					throw CompilerError { "Imported module must an existing file or a directory: " + dependecy_path.string() };
				}
			}
			else {
				throw CompilerError {"Import directive requires file path as quoted string", start.location};
			}
		}



		void process_source(
			const Source & source,
			ast::Program & ast,
			std::queue<Source> & pending_sources) {

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
			const Source & source = pending_sources.front();
			const std::filesystem::path path = source.get_full_name();
			const bool new_source = std::none_of(std::begin(known_sources), std::end(known_sources), [&] (auto & s) {
				return std::filesystem::exists(s) && std::filesystem::exists(path) && std::filesystem::equivalent(s, path);
			}); 
			if(new_source && path.extension() == ".ltn") {
				process_source(source, ast, pending_sources);
				known_sources.push_back(path);
				std::vector<Source> subsources = source.get_module_subsources(); 
				for(auto & s : subsources) {
					pending_sources.push(std::move(s));
				}
			}
			pending_sources.pop();
		}

		return ast;
	}
}