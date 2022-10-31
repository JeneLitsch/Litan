#pragma once
#include <cstdint>
#include <unordered_map>
#include <string>

namespace ltn {
	std::uint8_t read_version(auto & it) {
		return *(it++);
	}

	std::unordered_map<std::string, std::uint64_t> read_addr_table(auto & it) {
		static constexpr auto get_uint64 = [] (auto & it) {
			const auto value 
				= (static_cast<std::size_t>(*(it + 7)) << 8 * 0)
				+ (static_cast<std::size_t>(*(it + 6)) << 8 * 1)
				+ (static_cast<std::size_t>(*(it + 5)) << 8 * 2)
				+ (static_cast<std::size_t>(*(it + 4)) << 8 * 3)
				+ (static_cast<std::size_t>(*(it + 3)) << 8 * 4)
				+ (static_cast<std::size_t>(*(it + 2)) << 8 * 5)
				+ (static_cast<std::size_t>(*(it + 1)) << 8 * 6)
				+ (static_cast<std::size_t>(*(it + 0)) << 8 * 7);
			it += 8;
			return value;
		};

		std::unordered_map<std::string, std::uint64_t> table;

		const std::size_t table_size = get_uint64(it);
		for(std::size_t i = 0; i < table_size; ++i) {
			const std::size_t name_size = get_uint64(it);
			auto next = it + static_cast<long>(name_size);
			const std::string name { it, next };
			it = next;
			const std::uint64_t addr = get_uint64(it);
			table[name] = addr;
		}

		return table;
	}
}