#include "ltnvm/utils/cast.hxx"
#include "ltn/version.hxx"
#include <filesystem>
#include <fstream>
#include <iostream>
#include "ltn/args.hxx"
#include "stdxx/args.hxx"
#include "ltnc/Ltnc.hxx"
#include "ltnvm/VM.hxx"

std::vector<ltn::Any> args_str_to_any(const std::vector<std::string> & strings) {
	std::vector<ltn::Any> anys;
	std::ranges::transform(strings, std::back_inserter(anys), ltn::Any::from_string);
	return anys;
}

int main(int argc, char const *argv[]) {
	stx::args args{argc, argv};

	stx::option_description desc {
		"Litan Interpreter [ltn] " + std::string{ltn::version},
		"The Litan interpreter executes a number of Litan source files directly."
	};

	auto & flag_source = desc.add<stx::option_string_list>(
		{"--src"},
		"Source",
		"Specifies a list of source files to interpret."
	);

	auto & flag_o = desc.add<stx::option_flag>(
		{"-o"},
		"Optimization",
		"If this flag is set the compiler applies optimizations to the code");

	auto & flag_version = ltn::args::version(desc);
	auto & flag_help    = ltn::args::help(desc);
	auto & main_args    = ltn::args::main_args(desc);
	auto & main_init    = ltn::args::main_init(desc);

	args.parse_options(desc);

	if(flag_version) {
		std::cout << "Litan: " << ltn::version << "\n";
		return EXIT_SUCCESS;
	}
	if(flag_help) {
		std::cout << desc.describe(); 
		return EXIT_SUCCESS;
	}

	std::vector<std::string> single_file;
	if(argc > 1) {
		single_file.push_back(argv[1]);
	}

	ltn::vm::VM vm;
	try {
		std::vector<std::string> args;

		auto sources = ltn::c::read_sources(flag_source.value_or(single_file));
		auto source = ltn::c::parse(sources);
		auto program = ltn::c::analyze(source);
		if(flag_o) ltn::c::optimize(program);
		auto [instructions, link_info] = ltn::c::compile(program);
		if(flag_o) instructions = ltn::c::peephole(instructions);
		auto bytecode = ltn::c::assemble(instructions, link_info);
		const auto main_function = main_init.value_or("");
		vm.setup(bytecode);
		auto x = vm.call(main_function, args_str_to_any(main_args.value_or({})));
		std::cout << "Exit main() with return value: " << x << "\n";
	}
	catch (const ltn::c::CompilerError & error) {
		std::cout << error << "\n";
		return EXIT_FAILURE;
	}
	catch (const std::runtime_error & error) {
		std::cout << error.what() << "\n";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
