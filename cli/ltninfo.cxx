#include "ltn/header.hxx"
#include <fstream>
#include <iostream>
#include <vector>

void print_table(const auto & table) {
	for(const auto & [name, addr] : table) {
		std::cout << "\t" << name << " : " << addr << "\n";
	}
}

int main(int, char const *argv[]) {
	std::ifstream file{argv[1]};
	const std::vector<std::uint8_t> bytecode {
		std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>()
	};
	
	auto it = std::begin(bytecode);

	const std::uint64_t version = ltn::read_version(it);

	std::cout << "Litan File Info" << "\n";
	std::cout << "version: " << version << "\n";

	if(version == 3) {
		const auto function_table = ltn::read_addr_table(it);
		std::cout << "function table: " << "\n";
		print_table(function_table);

		const auto static_table = ltn::read_addr_table(it);
		std::cout << "global table: " << "\n";
		print_table(static_table);

		return EXIT_SUCCESS;
	}

	std::cout << "Unknown file version\n";
	return EXIT_FAILURE;
}
