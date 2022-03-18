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


	std::vector<ast::glob_ptr> enumeration(lex::Lexer & lexer,ast::Namespace namespaze) {
		std::vector<ast::glob_ptr> globals;
		
		const auto enum_name = parse::name(lexer);
		namespaze.push_back(enum_name);
		open(lexer);
		
		const auto values = parse::values(lexer);
		for(const auto & [key, value] : values) {
			const auto loc = lexer.location();
			auto global = std::make_unique<ast::Global>(loc);
			global->literal = std::make_unique<ast::Enum>(value, loc);
			global->name = key;
			global->namespaze = namespaze;
			globals.push_back(std::move(global));
		}
		
		close(lexer);

		return globals;
	}
}