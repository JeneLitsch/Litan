#include "parse.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;
	
		std::optional<std::int64_t> explicit_value(Tokens & tokens) {
			if(match(TT::COLON, tokens)) {
				if(auto expr = parse_integral(tokens)) {
					return static_cast<ast::Integer&>(*expr).value;
				}
				throw CompilerError{"Expected integer litaral", location(tokens)};
			}
			return std::nullopt;
		}



		std::map<std::string, std::int64_t> parse_values(Tokens & tokens) {
			std::map<std::string, std::int64_t> values;
			std::int64_t value = 0;
			while(auto value_name = match(TT::INDENTIFIER, tokens)) {
				if(values.contains(value_name->str)) {
					throw CompilerError{"Redefinition of enum value"};
				}
				if(auto v = explicit_value(tokens)) {
					value = *v;
				}
				values.insert({value_name->str, value});
				semicolon(tokens);
				++value;
			}
			return values;
		}
	}


	ast::enum_ptr parse_enumeration(Tokens & tokens, Namespace namespaze) {
		
		const auto enum_name = parse_enum_name(tokens);
		auto enumeration = stx::make_unique<ast::Enumeration>(
			location(tokens),
			enum_name,
			namespaze);

		brace_l(tokens);
		
		const auto values = parse_values(tokens);
		for(const auto & [key, value] : values) {
			const auto loc = location(tokens);
			auto integer = stx::make_unique<ast::Integer>(value, loc);
			enumeration->labels.push_back({
				key,
				std::move(integer)});
		}
		
		brace_r(tokens);

		return enumeration;
	}
}