#pragma once
#include <map>
#include <string>
#include <cstdint>

namespace ltn {
	enum class ReservedMemberCode {
		OPERATOR_ADD = 0x10, OPERATOR_SUB, OPERATOR_MLT, OPERATOR_DIV, OPERATOR_MOD, OPERATOR_POW,
		OPERATOR_STR = 0x20, OPERATOR_CMP, OPERATOR_BOOL,

		SIZE = 0x40, IS_EMTPY, AT,
		PUSH, POP,
		BACK, FRONT, PEEK,
		INSERT, ERASE,
		KEYS, VALUES, MERGED, SPLIT,
		FILTER, TRANSFORM, REDUCE, REVERSED, ZIPPED,
		SLICE, PREFIX, SUFFIX,
		ANY, ALL, NONE, HAS, 
	};

	extern const std::map<std::string, std::uint64_t> reserved_member_name_to_code;
}
	