#include "parse.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;
	}


	ast::prst_ptr parse_preset(Tokens & tokens, const ast::Namespace & namespaze) {
		if(auto start = match(TT::PRESET, tokens)) {
			const auto name = parse_preset_name(tokens);
			std::vector<ast::Preset::Member> members;
			brace_l(tokens);
			while(match(TT::VAR, tokens)) {
				const auto name = parse_variable_name(tokens);
				auto type = parse_var_type(tokens);
				members.push_back(ast::Preset::Member{
					.name = name,
					.type = type
				});
				semicolon(tokens);
			}
			brace_r(tokens);
			return std::make_unique<ast::Preset>(
				start->location,
				name,
				namespaze,
				members);
		}
		else return nullptr;
	}
}