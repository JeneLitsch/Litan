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



	ast::glob_ptr parse_definition(Tokens & tokens, const ast::Namespace & namespaze) {
		if(match(TT::DEFINE, tokens)) {
			const auto name = parse_name(tokens);
			auto global = std::make_unique<ast::Global>(
				location(tokens),
				name,
				namespaze);
			parse_equal_sign(tokens);
			global->expr = parse_static_expression(tokens);
			semicolon(tokens);
			return global;
		}
		return nullptr;
	}
}