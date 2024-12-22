#include "reserved_members.hxx"
#include <array>
#include <algorithm>

namespace ltn {
	struct ReservedMember {
		std::string name;
		ReservedMemberCode code;
	};

	const auto reserved_members = std::to_array<ReservedMember>({
		{"__add__", ReservedMemberCode::OPERATOR_ADD},
		{"__sub__", ReservedMemberCode::OPERATOR_SUB},
		{"__mlt__", ReservedMemberCode::OPERATOR_MLT},
		{"__div__", ReservedMemberCode::OPERATOR_DIV},
		{"__mod__", ReservedMemberCode::OPERATOR_MOD},
		{"__pow__", ReservedMemberCode::OPERATOR_POW},
		{"__cmp__", ReservedMemberCode::OPERATOR_CMP},
		{"__str__", ReservedMemberCode::OPERATOR_STR},
		{"__bool__", ReservedMemberCode::OPERATOR_BOOL},

		{"size",        ReservedMemberCode::SIZE},
		{"is_empty",    ReservedMemberCode::IS_EMTPY},
		{"push",        ReservedMemberCode::PUSH},
		{"pop",         ReservedMemberCode::POP},
		{"peek",        ReservedMemberCode::PEEK},
		{"back",        ReservedMemberCode::BACK},
		{"front",       ReservedMemberCode::FRONT},
		{"at",          ReservedMemberCode::AT},
		{"insert",      ReservedMemberCode::INSERT},
		{"erase",       ReservedMemberCode::ERASE},
		{"has",         ReservedMemberCode::HAS},
		{"keys",        ReservedMemberCode::KEYS},
		{"values",      ReservedMemberCode::VALUES},
		{"filter",      ReservedMemberCode::FILTER},
		{"transform",   ReservedMemberCode::TRANSFORM},
		{"reduce",      ReservedMemberCode::REDUCE},
		{"any",         ReservedMemberCode::ANY},
		{"all",         ReservedMemberCode::ALL},
		{"none",        ReservedMemberCode::NONE},
		{"slice",       ReservedMemberCode::SLICE},
		{"prefix",      ReservedMemberCode::PREFIX},
		{"suffix",      ReservedMemberCode::SUFFIX},
		{"reversed",    ReservedMemberCode::REVERSED},
		{"merged",      ReservedMemberCode::MERGED},
		{"zipped",      ReservedMemberCode::ZIPPED},
	});


	const std::map<std::string, std::uint64_t> reserved_member_name_to_code = [] {
		std::map<std::string, std::uint64_t> map;
		for(const ReservedMember & member : reserved_members) {
			map.insert({member.name, static_cast<std::uint64_t>(member.code)});
		}
		return map;
	}();
}