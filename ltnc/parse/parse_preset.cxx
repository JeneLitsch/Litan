#include "parse.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;
	}


	ast::prst_ptr parse_preset(Tokens & tokens, const Namespace & namespaze) {
		if(auto start = match(TT::PRESET, tokens)) {
			const auto name = parse_preset_name(tokens);
			std::vector<ast::Preset::Member> members;
			brace_l(tokens);
			while(match(TT::VAR, tokens)) {
				auto name = parse_variable_name(tokens);
				auto type = parse_var_type(tokens);
				members.push_back(ast::Preset::Member{
					.name = std::move(name),
					.type = std::move(type),
				});
				semicolon(tokens);
			}
			brace_r(tokens);
			return std::make_unique<ast::Preset>(
				start->location,
				name,
				namespaze,
				std::move(members)
			);
		}
		else return nullptr;
	}
}