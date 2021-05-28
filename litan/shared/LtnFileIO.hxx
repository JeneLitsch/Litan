#pragma once
#include <vector>
#include <string>
namespace ltn {
	std::string readFile(const std::string filename);
	void writeFile(const std::string & filename, const std::string content);
	
	std::string toHex(const std::vector<std::uint64_t> byteCode);
	std::vector<std::uint64_t> fromHex(const std::string & hexCode);

	std::string toBin(const std::vector<std::uint64_t> byteCode);
	std::vector<std::uint64_t> fromBin(const std::string & binCode);
}