#include "parse.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;
		ast::Reflect::Query parse_namespace_query(Tokens & tokens) {
			auto [name, namespaze] = parse_symbol(tokens);
			namespaze.push_back(name);
			return ast::Reflect::NamespaceQuery {
				.namespaze = namespaze
			};
		}


		
		ast::Reflect::Query parse_function_query(Tokens & tokens) {
			auto [name, namespaze] = parse_symbol(tokens);
			auto arity = match(TT::PAREN_L, tokens) ? parse_placeholder(tokens) : 0;
			return ast::Reflect::FunctionQuery {
				.namespaze = namespaze,
				.name = name,
				.arity = arity,
			};
		}



		ast::Reflect::Query parse_line_query(Tokens &) {
			return ast::Reflect::LineQuery{};
		}



		ast::Reflect::Query parse_file_query(Tokens &) {
			return ast::Reflect::FileQuery{};
		}



		ast::Reflect::Query parse_location_query(Tokens &) {
			return ast::Reflect::LocationQuery{};
		}



		ast::Reflect::Query parse_query(Tokens & tokens) {
			if(match(TT::NAMESPACE, tokens)) return parse_namespace_query(tokens);
			if(match(TT::FUNCTION, tokens))  return parse_function_query(tokens);
			if(auto t = match(TT::INDENTIFIER, tokens)) {
				if(t->str == "line")     return parse_line_query(tokens);
				if(t->str == "file")     return parse_file_query(tokens);
				if(t->str == "location") return parse_location_query(tokens);
			}
			
			throw CompilerError {
				"Unknown reflection query", tokens.front().location 
			};
		}
	}


	ast::expr_ptr parse_reflect(Tokens & tokens) {
		if(auto ref = match(TT::REFLECT, tokens)) {
			if(!match(TT::PAREN_L, tokens)) throw CompilerError {
				"Expected ( after reflect", ref->location 
			};

			auto query = parse_query(tokens);

			if(!match(TT::PAREN_R, tokens)) throw CompilerError {
				"Expected ) after reflect", ref->location 
			};

			return stx::make_unique<ast::Reflect>(query, ref->location);
		}
		else return nullptr;
	}
}