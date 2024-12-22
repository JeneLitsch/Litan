#pragma once
#include <unordered_map>
#include <cstdint>
#include <variant>
#include <string>
#include "ltn/reserved_members.hxx"

namespace ltn::c {
	class MemberTable {
	public:
		MemberTable();
		std::uint64_t get_id(const std::string & str);
		const auto & get_table() const { return table; } 
	private:
		std::uint64_t next_id = 256;
		std::unordered_map<std::string, std::uint64_t> table;
	};
}