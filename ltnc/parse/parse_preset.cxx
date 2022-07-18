#include "parse.hxx"

namespace ltn::c {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}


	ast::prst_ptr parse_preset(Tokens & tokens, const ast::Namespace & namespaze) {
		if(auto start = match(TT::PRESET, tokens)) {
			const auto name = parse_preset_name(tokens);
			std::vector<std::string> member_names;
			brace_l(tokens);
			while(match(TT::VAR, tokens)) {
				const auto name = parse_variable_name(tokens);
				member_names.push_back(name);
				semicolon(tokens);
			}
			brace_r(tokens);
			return std::make_unique<ast::Preset>(
				start->location,
				name,
				namespaze,
				member_names);
		}
		else return nullptr;
	}
}