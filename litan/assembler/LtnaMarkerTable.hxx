#pragma once
#include <string>
#include <cstdint>
#include <unordered_map>
namespace ltna {
	class MarkerTable {
	public:
		void clear();
		void add(const std::string & name, std::uint64_t addr);
		std::uint64_t find(const std::string & name) const;
		bool contains(const std::string & name) const;
	private:
		std::unordered_map<std::string, std::uint64_t> markers;
	};
}