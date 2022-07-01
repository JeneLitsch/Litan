#include "parse.hxx"

namespace ltn::c {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}


	ast::prst_ptr parse_preset(lex::Lexer & lexer, const ast::Namespace & namespaze) {
		if(auto start = lexer.match(TT::PRESET)) {
			const auto name = parse_preset_name(lexer);
			std::vector<std::string> member_names;
			brace_l(lexer);
			while(lexer.match(TT::VAR)) {
				const auto name = parse_variable_name(lexer);
				member_names.push_back(name);
				semicolon(lexer);
			}
			brace_r(lexer);
			return std::make_unique<ast::Preset>(
				start->location,
				name,
				namespaze,
				member_names);
		}
		else return nullptr;
	}
}