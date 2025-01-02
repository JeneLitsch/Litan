#pragma once
#include <map>
#include <string>
#include <span>
#include <vector>
#include <cstdint>
#include <optional>

namespace ltn {
	class StaticPool {
	public:
		StaticPool() = default;
		virtual ~StaticPool() = default;
		
		// Serialization
		void read(std::span<const std::uint8_t>::iterator & it);
		void write(std::vector<std::uint8_t> & bytecode) const;

		void insert(std::uint64_t id, std::string str);
		std::optional<std::uint64_t> at(std::string str) const;
		std::map<std::string, std::uint64_t> name_to_address;
	private:
	};
}