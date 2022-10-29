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

		ast::Reflect::Query parse_query(Tokens & tokens) {
			if(match(TT::NAMESPACE, tokens)) return parse_namespace_query(tokens);
			throw CompilerError {
				"Expected ) after reflect", tokens.front().location 
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

			return std::make_unique<ast::Reflect>(query, ref->location);
		}
		else return nullptr;
	}
}