#pragma once
#include <cstdint>
#include <unordered_map>
#include <string>

#include "file/binary.hxx"

namespace ltn {
	inline std::uint8_t read_version(auto & it) {
		return *(it++);
	}





	inline std::unordered_map<std::string, std::uint64_t> read_addr_table(auto & it) {
		std::unordered_map<std::string, std::uint64_t> table;

		const std::size_t table_size = read_u64(it);
		for(std::size_t i = 0; i < table_size; ++i) {
			const std::size_t name_size = read_u64(it);
			auto next = it + static_cast<long>(name_size);
			const std::string name { it, next };
			it = next;
			const std::uint64_t address = read_u64(it);
			table[name] = address;
		}

		return table;
	}



	inline std::unordered_map<std::uint64_t, std::string> read_name_table(auto & it) {
		std::unordered_map<std::uint64_t, std::string> table;

		const std::size_t table_size = read_u64(it);
		for(std::size_t i = 0; i < table_size; ++i) {
			const std::size_t name_size = read_u64(it);
			auto next = it + static_cast<long>(name_size);
			const std::string name { it, next };
			it = next;
			const std::uint64_t address = read_u64(it);
			table[address] = name;
		}

		return table;
	}
}