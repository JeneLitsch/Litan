#include "parse.hxx"

namespace ltn::c {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	
		std::string parse_name(Tokens & tokens) {
			if(auto t = match(TT::INDENTIFIER, tokens)) {
				return t->str;
			}
			throw CompilerError{"Expected definition name", tokens.location()};
		}



		std::string parse_equal_sign(Tokens & tokens) {
			if(auto t = match(TT::ASSIGN, tokens)) {
				return t->str;
			}
			throw CompilerError{"Expected =", tokens.location()};
		}
	}



	ast::glob_ptr parse_definition(Tokens & tokens, const ast::Namespace & namespaze) {
		if(match(TT::DEFINE, tokens)) {
			const auto name = parse_name(tokens);
			auto global = std::make_unique<ast::Global>(
				tokens.location(),
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