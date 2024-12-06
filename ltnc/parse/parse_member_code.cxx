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
			{"add", MemberCode::OPERATOR_ADD},
			{"sub", MemberCode::OPERATOR_SUB},
			{"mlt", MemberCode::OPERATOR_MLT},
			{"div", MemberCode::OPERATOR_DIV},
			{"mod", MemberCode::OPERATOR_MOD},
			{"pow", MemberCode::OPERATOR_POW},
			{"cmp", MemberCode::OPERATOR_CMP},
			{"str", MemberCode::OPERATOR_STR},
			{"bool", MemberCode::OPERATOR_BOOL},
		};


		for(const auto & [name, code] : table) {
			if(match(name, tokens)) return code;
		}

		throw invalid_operator(tokens);
	}
}