#pragma once
#include <cstdint>
#include <span>
#include <vector>
#include <string>

namespace ltn {
	class StringPool {
	public:
		StringPool() = default;
		virtual ~StringPool() = default;

		void read(std::span<const std::uint8_t>::iterator & it);
		void write(std::vector<std::uint8_t> & bytecode) const;

		std::uint64_t push(std::string str);

		std::uint64_t size() const;
		std::string_view operator[](std::uint64_t i) const;
	private:
		std::vector<std::string> data;
	};
}