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
	if (argc < 3) {
		return EXIT_FAILURE;
	}
	const char * dest_name = argv[1];
	const std::filesystem::path dest_h = std::filesystem::path{dest_name}.replace_extension(".h");
	const std::filesystem::path dest_c = std::filesystem::path{dest_name}.replace_extension(".c");
	
	std::ofstream output_h { dest_h };
	std::ofstream output_c { dest_c };

	output_h << "#pragma once \n\n";
	output_c << "#include " << dest_h.filename() << "\n\n";
	std::span<const char *> srcs = { argv + 2, argv + argc };
	for (const char * src : srcs) {
		std::filesystem::path src_path = src;
		std::ifstream input { src_path };
		
		std::cout << src << "\n";

		const std::string data = read_entire_file(input);

		const std::string var_name = std::filesystem::path(dest_name).stem().concat("_").concat(src_path.stem().string()).string();

		output_h << "extern const char * " << var_name << ";\n";
		output_c << "const char * " << var_name << " = \""; 
		for (char c : data) {
			switch (c) {
				case '\n': output_c << "\\n";  break;
				case '\t': output_c << "\\t";  break;
				case '\\': output_c << "\\\\"; break;
				case '\"': output_c << "\\\""; break;
				default  : output_c << c;      break;
			}
		}
		output_c << "\";\n";
	}

	return EXIT_SUCCESS;
}
