#include "dump.hxx"
#include "litan/shared/options.hxx"
#include "litan/shared/file.hxx"
#include "litan_compiler/Ltnc.hxx"


DumpOptions parse_dump_options(std::span<const std::string_view> options) {
	DumpOptions dump_options;
	for (std::string_view option : options) {
		if(!read_dump_option(dump_options, option)) {
			std::cout << "[Warning] Unknown option: " << option << "\n";
		}
	}
	return dump_options;
}

int dump(std::span<const std::string_view> args) {
	std::span<const std::string_view> flags = cut_options(args);
	std::span<const std::string_view> rest = args.subspan(flags.size());
	DumpOptions options = parse_options<DumpOptions, read_dump_option>(flags);
	
	if(rest.size() < 2) {
		throw std::runtime_error{"Invalid dump arguments"};
	}

	std::string_view script_path = rest[0];
	std::string_view target_path = rest[1];

	std::cout << "Compiling script...\n";
	std::cout << "[Source] " << script_path << "\n";
	std::cout << "[Target] " << target_path << "\n";
	auto sources = ltn::c::read_sources({script_path});
	auto ast = ltn::c::parse(sources);
	auto sst = ltn::c::analyze(ast, options.build.analysis);
	auto instructions = ltn::c::compile(sst, options.build.compilation);
	auto ofile = open_file(target_path, std::ios::openmode(0));
	ofile << ltn::c::print(instructions.instructions);
	std::cout << "Done!\n";
	return EXIT_SUCCESS;
}
