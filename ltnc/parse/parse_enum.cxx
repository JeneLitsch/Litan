#include "parse.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	
		std::string name(lex::Lexer & lexer) {
			if(auto t = lexer.match(TT::INDENTIFIER)) {
				return t->str;
			}
			throw CompilerError{"Expected enum name", lexer.location()};
		}



		void open(lex::Lexer & lexer) {
			if(!lexer.match(TT::BRACE_L)) {
				throw CompilerError{"Expected {", lexer.location()};
			}
		}


		
		void close(lex::Lexer & lexer) {
			if(!lexer.match(TT::BRACE_R)) {
				throw CompilerError{"Expected }", lexer.location()};
			}
		}



		std::optional<std::int64_t> explicit_value(lex::Lexer & lexer) {
			if(lexer.match(TT::COLON)) {
				if(auto expr = integral(lexer)) {
					return static_cast<ast::Integer&>(*expr).value;
				}
				throw CompilerError{"Expected integer litaral", lexer.location()};
			}
			return std::nullopt;
		}



		std::map<std::string, std::int64_t> values(lex::Lexer & lexer) {
			std::map<std::string, std::int64_t> values;
			std::int64_t value = 0;
			while(auto value_name = lexer.match(TT::INDENTIFIER)) {
				if(values.contains(value_name->str)) {
					throw CompilerError{"Redefinition of enum value"};
				}
				if(auto v = explicit_value(lexer)) {
					value = *v;
				}
				values.insert({value_name->str, value});
				semicolon(lexer);
				++value;
			}
			return values;
		}
	}



	ast::enum_ptr enumeration(lex::Lexer & lexer, const ast::Namespace & namespaze) {
		if(lexer.match(TT::ENUM)) {
			auto enym = std::make_unique<ast::Enum>(lexer.location());
			enym->name = parse::name(lexer);
			enym->namespaze = namespaze;
			parse::open(lexer);
			enym->values = parse::values(lexer);
			parse::close(lexer);
			return enym;
		}
		return nullptr;
	}
}