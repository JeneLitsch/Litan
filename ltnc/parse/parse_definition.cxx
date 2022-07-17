#include "parse.hxx"

namespace ltn::c {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	
		std::string parse_name(LexBuffer & lexer) {
			if(auto t = lexer.match(TT::INDENTIFIER)) {
				return t->str;
			}
			throw CompilerError{"Expected definition name", lexer.location()};
		}



		std::string parse_equal_sign(LexBuffer & lexer) {
			if(auto t = lexer.match(TT::ASSIGN)) {
				return t->str;
			}
			throw CompilerError{"Expected =", lexer.location()};
		}
	}



	ast::glob_ptr parse_definition(LexBuffer & lexer, const ast::Namespace & namespaze) {
		if(lexer.match(TT::DEFINE)) {
			const auto name = parse_name(lexer);
			auto global = std::make_unique<ast::Global>(
				lexer.location(),
				name,
				namespaze);
			parse_equal_sign(lexer);
			global->expr = parse_static_expression(lexer);
			semicolon(lexer);
			return global;
		}
		return nullptr;
	}
}