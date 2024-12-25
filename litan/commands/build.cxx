#include "build.hxx"
#include <iostream>
#include "litan_compiler/Ltnc.hxx"
#include "../shared/shared.hxx"
#include "../shared/file.hxx"

int build(std::span<const std::string_view> args) {
	std::string_view script_path = args[0];
	std::string_view target_path = args[1];
	
	auto sources = ltn::c::read_sources({script_path});
	auto ast = ltn::c::parse(sources);
	auto sst = ltn::c::analyze(ast);
	auto instructions = ltn::c::compile(sst);
	auto bytecode = ltn::c::assemble(instructions);

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
