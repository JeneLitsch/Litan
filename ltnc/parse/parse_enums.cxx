#include "parse.hxx"
#include "stdxx/functional.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;
	
		std::optional<std::int64_t> explicit_value(Tokens & tokens) {
			if(match(TT::COLON, tokens)) {
				auto expr = parse_expression(tokens);
				if(auto integer = dynamic_cast<ast::Integer*>(expr.get())) {
					return integer->value;
				}
				throw CompilerError{"Expected integer literal", location(tokens)};
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

		brace_l(tokens);

		auto to_labels = stx::fx::mapped([] (const auto & pair) {
			return ast::Enumeration::Label { pair.first, pair.second };
		});

		auto labels = to_labels(parse_values(tokens));

		brace_r(tokens);

		return std::make_unique<ast::Enumeration>(
			location(tokens),
			enum_name,
			namespaze,
			std::move(labels)
		);
	}
}