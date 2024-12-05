#include "compile.hxx"
#include <iostream>
#include "ltnc/Ltnc.hxx"
#include "../shared/shared.hxx"
#include "../shared/file.hxx"

int compile(std::string_view script_path, std::string_view target_path) {
	auto sst = analysis_phase(script_path);
	auto instructions = synthesis_phase(sst);
	auto link_info = ltn::c::link(sst, instructions);
	auto bytecode = ltn::c::assemble(instructions, link_info);

	std::cout << "Compiling script...\n";
	auto ofile = open_file(target_path, std::ios::binary);
	std::cout << "[Source] " << script_path << "\n";
	std::cout << "[Target] " << target_path << "\n";
	for(std::uint8_t byte : bytecode) {
		ofile << byte;
	}
	std::cout << "Done!\n";
	return EXIT_SUCCESS;
}
