#pragma once
#include <unordered_map>
#include <cstdint>
#include <variant>
#include <string>
#include "ltn/MemberCode.hxx"

namespace ltn::c {
	class MemberTable {
	public:
		std::uint64_t get_id(const std::string & str);
		const auto & get_table() const { return table; } 
	private:
		std::unordered_map<std::string, std::uint64_t> table;
	};
}