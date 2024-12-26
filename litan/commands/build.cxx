#include "build.hxx"
#include <iostream>
#include "litan_compiler/Ltnc.hxx"
#include "litan/shared/file.hxx"
#include "litan/shared/options.hxx"

int build(std::span<const std::string_view> args) {

	std::span<const std::string_view> flags = cut_options(args);
	std::span<const std::string_view> rest = args.subspan(flags.size());
	BuildOptions options = parse_options<BuildOptions, read_build_option>(flags);

	if(rest.size() < 2) {
		throw std::runtime_error{"Invalid build arguments"};
	}

	std::string_view script_path = rest[0];
	std::string_view target_path = rest[1];
	
	auto sources = ltn::c::read_sources({script_path});
	auto ast = ltn::c::parse(sources);
	auto sst = ltn::c::analyze(ast, options.analysis);
	auto instructions = ltn::c::compile(sst, options.compilation);
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
