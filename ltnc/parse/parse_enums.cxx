#include "parse.hxx"

namespace ltn::c {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	
		std::optional<std::int64_t> explicit_value(lex::Lexer & lexer) {
			if(lexer.match(TT::COLON)) {
				if(auto expr = parse_integral(lexer)) {
					return static_cast<ast::Integer&>(*expr).value;
				}
				throw CompilerError{"Expected integer litaral", lexer.location()};
			}
			return std::nullopt;
		}



		std::map<std::string, std::int64_t> parse_values(lex::Lexer & lexer) {
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


	ast::enum_ptr parse_enumeration(lex::Lexer & lexer, ast::Namespace namespaze) {
		
		const auto enum_name = parse_enum_name(lexer);
		auto enumeration = std::make_unique<ast::Enumeration>(
			lexer.location(),
			enum_name,
			namespaze);

		brace_l(lexer);
		
		const auto values = parse_values(lexer);
		for(const auto & [key, value] : values) {
			const auto loc = lexer.location();
			auto integer = std::make_unique<ast::Integer>(value, loc);
			enumeration->labels.push_back({
				key,
				std::move(integer)});
		}
		
		brace_r(lexer);

		return enumeration;
	}
}