#include "parse.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	
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
		
		const auto enum_name = parse::enum_name(lexer);
		namespaze.push_back(enum_name);
		brace_l(lexer);
		
		const auto values = parse::values(lexer);
		for(const auto & [key, value] : values) {
			const auto loc = lexer.location();
			auto global = std::make_unique<ast::Global>(loc, key, namespaze);
			global->expr = std::make_unique<ast::Enum>(value, loc);
			globals.push_back(std::move(global));
		}
		
		brace_r(lexer);

		return globals;
	}
}