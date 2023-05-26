#include "parse.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;

		CompilerError invalid_operator(Tokens & tokens) {
			return CompilerError{"Invalid operator", location(tokens)};
		}
	}
	


	MemberCode parse_member_code(Tokens & tokens) {
		const static std::map<std::string, MemberCode> table {
			{"add", MemberCode::ADD},
			{"sub", MemberCode::SUB},
			{"mlt", MemberCode::MLT},
			{"div", MemberCode::DIV},
			{"mod", MemberCode::MOD},
			{"pow", MemberCode::POW},
			{"cmp", MemberCode::CMP},
			{"str", MemberCode::STR},
			{"bool", MemberCode::BOOL},
		};


		for(const auto & [name, code] : table) {
			if(match(name, tokens)) return code;
		}

		throw invalid_operator(tokens);
	}
}