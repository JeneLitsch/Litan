#pragma once
#include <unordered_map>
#include <cstdint>
#include <string>

namespace ltn::c {
	class MemberTable {
	public:
		std::uint64_t get_id(const std::string & str);
	private:
		std::unordered_map<std::string, std::uint64_t> table;
	};
}