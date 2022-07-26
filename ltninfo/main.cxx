#include "ltn/header.hxx"
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
	std::ifstream file{argv[1]};
	const std::vector<std::uint8_t> bytecode {
		std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>()
	};
	
	auto it = std::begin(bytecode);

	const std::uint64_t version = ltn::read_version(it);
	const auto fx_table = ltn::read_fx_table(it);

	std::cout << "Litan File Info" << "\n";
	std::cout << "version: " << version << "\n";

	if(version == 3) {
		std::cout << "fx table: " << "\n";
		for(const auto & [name, addr] : fx_table) {
			std::cout << "\t" << name << " : " << addr << "\n";
		}
		return EXIT_SUCCESS;
	}

	std::cout << "Unknown file version\n";
	return EXIT_FAILURE;
}
