#include <cstdlib>
#include <span>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <algorithm>

std::string read_entire_file(std::ifstream & fin) {
    std::ostringstream oss;
    oss << fin.rdbuf();
    return oss.str();
}

int main(int argc, char const *argv[]) {
	if (argc < 2) {
		return EXIT_FAILURE;
	}
	const char * namespace_name = argv[1];
	const char * dest_name = argv[2];
	std::span<const char *> srcs = { argv + 3, argv + argc };

	const std::filesystem::path dest_c = std::filesystem::path{dest_name}.replace_extension(".cxx");
	std::ofstream output { dest_c };
	output << "namespace " << namespace_name << "{\n";
	for (const char * src : srcs) {
		std::filesystem::path src_path = src;
		std::ifstream input { src_path };
		
		std::cout << "     |- " << src << "\n";

		const std::string data = read_entire_file(input);

		const std::string var_name = src_path.stem().string();

		output << "const char * " << var_name << " = \""; 
		for (char c : data) {
			switch (c) {
				case '\n': output << "\\n";  break;
				case '\t': output << "\\t";  break;
				case '\\': output << "\\\\"; break;
				case '\"': output << "\\\""; break;
				default  : output << c;      break;
			}
		}
		output << "\";\n";
	}
		output << "}\n";

	return EXIT_SUCCESS;
}
