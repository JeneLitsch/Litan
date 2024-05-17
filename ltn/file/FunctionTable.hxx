#pragma once
#include <vector>
#include <cstdint>
#include <string>
#include <span>

namespace ltn {
	class FunctionTable {
	public:
		struct Entry {
			std::uint64_t address;
			std::string name;
		};

		FunctionTable();
		const Entry * operator[](std::uint64_t id) const;
		const Entry * find_by_name(const std::string_view name) const;
		bool contains(const std::string_view name) const;
		void push_back(Entry entry);

		void read(std::span<const std::uint8_t>::iterator & it);
		void write(std::vector<std::uint8_t> & bytecode) const;

		virtual ~FunctionTable();

	private:
		std::vector<Entry> entries;
	};
}