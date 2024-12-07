#include "parse.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;

		CompilerError invalid_operator(Tokens & tokens) {
			return CompilerError{"Invalid operator", location(tokens)};
		}
	}
	


	MemberCode parse_operator_overload_code(Tokens & tokens) {
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



	std::optional<MemberCode> parse_reserved_member_name(Tokens & tokens) {
		const static std::map<std::string, MemberCode> table {
			{"size",      MemberCode::SIZE},
			{"is_empty",  MemberCode::IS_EMTPY},
			{"push",      MemberCode::PUSH},
			{"pop",       MemberCode::POP},
			{"peek",      MemberCode::PEEK},
			{"back",      MemberCode::BACK},
			{"front",     MemberCode::FRONT},
			{"at",        MemberCode::AT},
			{"insert",    MemberCode::INSERT},
			{"erase",     MemberCode::ERASE},
			{"has",       MemberCode::HAS},
			{"keys",      MemberCode::KEYS},
			{"values",    MemberCode::VALUES},
			{"filter",    MemberCode::FILTER},
			{"transform", MemberCode::TRANSFORM},
			{"reduce",    MemberCode::REDUCE},
			{"any",       MemberCode::ANY},
			{"all",       MemberCode::ALL},
			{"none",      MemberCode::NONE},
		};

		for(const auto & [name, code] : table) {
			if(match(name, tokens)) {
				return code;
			}
		}
		return std::nullopt;
	}



	std::variant<std::string, MemberCode> parse_member(Tokens & tokens) {
		if(auto member = match(TT::BRACE_L, tokens)) {
			MemberCode code = parse_operator_overload_code(tokens);
			if(!match(TT::BRACE_R, tokens)) {
				throw CompilerError{"Expected }", location(tokens)};
			}
			return code;
		}
		else if(auto code = parse_reserved_member_name(tokens)) {
			return *code;
		}
		else if(auto member = match(TT::INDENTIFIER, tokens)) {
			return member->str;
		}
		else {
			throw CompilerError {
				"Expected identifier for member access",
				location(tokens)
			};
		}
	}
}