#include "parse.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;
	
		std::string parse_name(Tokens & tokens) {
			if(auto t = match(TT::INDENTIFIER, tokens)) {
				return t->str;
			}
			throw CompilerError{"Expected definition name", location(tokens)};
		}



		std::string parse_equal_sign(Tokens & tokens) {
			if(auto t = match(TT::ASSIGN, tokens)) {
				return t->str;
			}
			throw CompilerError{"Expected =", location(tokens)};
		}
	}



	ast::defn_ptr parse_definition(Tokens & tokens, const Namespace & namespaze) {
		if(match(TT::DEFINE, tokens)) {
			auto name = parse_name(tokens);
			auto definition = std::make_unique<ast::Definition>(
				location(tokens),
				std::move(name),
				std::move(namespaze)
			);
			parse_equal_sign(tokens);
			definition->expr = parse_expression(tokens);
			semicolon(tokens);
			return definition;
		}
		return nullptr;
	}
}