#pragma once
#include <unordered_map>
#include <string>
#include <cstdint>
#include <istream>

namespace ltn::a::linking {
	using AddressTable = std::unordered_map<std::string, std::uint64_t>;

	AddressTable scan(std::istream & in);
	void patch(std::istream & in, std::ostream & out, const AddressTable & table);

	bool isJumpMark(std::string_view inst);
}