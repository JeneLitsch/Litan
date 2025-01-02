#pragma once
#include <map>
#include <string>
#include <cstdint>
#include <vector>
#include <optional>
#include <span>

namespace ltn {
	class MemberNameTable {
	public:
		MemberNameTable() = default;
		virtual ~MemberNameTable() = default;
		
		// Serialization
		void read(std::span<const std::uint8_t>::iterator & it);
		void write(std::vector<std::uint8_t> & bytecode) const;

		void insert(std::uint64_t id, std::string str);
		std::optional<std::string_view> at(std::uint64_t id) const;
	private:
		std::map<std::uint64_t, std::string> id_to_name;
	};
}