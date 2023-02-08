#include "Litan.hxx"
#include "ltnvm/cast.hxx"
#include "ltn/version.hxx"
#include <filesystem>
#include <fstream>
#include <iostream>
#include "ltn/args.hxx"
#include "stdxx/args.hxx"


int main(int argc, char const *argv[]) {
	stx::args args{argc, argv};

	stx::option_description desc {
		"Litan Interpreter [ltn] " + std::string{ltn::version},
		"The Litan interpreter executes a number of Litan source files directly."
	};

	auto & flag_o = desc.add<stx::option_flag>(
		{"-o"},
		"Optimization",
		"If this flag is set the compiler applies optimizations to the code"
	);

	auto & flag_version = ltn::args::version(desc);
	auto & flag_help    = ltn::args::help(desc);
	auto & main_args    = ltn::args::main_args(desc);
	auto & main_init    = ltn::args::main_init(desc);

	auto rest = desc.parse(args);

	std::vector<std::filesystem::path> files;
	while(rest) files.push_back((rest++).str_v());

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

	ltn::c::Reporter reporter;
	ltn::LtnVM vm;
	try {
		std::vector<std::string> args;
		std::vector<ltn::c::Source> sources;
		for(const auto & file : files) {
			sources.push_back(ltn::c::FileSource{file});
		}

		auto lexer = ltn::c::lex(sources, reporter);
		auto source = ltn::c::parse(lexer, reporter);
		auto program = ltn::c::analyze(source, reporter);
		if(flag_o) ltn::c::optimize(program);
		auto [instructions, link_info] = ltn::c::compile(program, reporter);
		if(flag_o) instructions = ltn::c::peephole(instructions);
		auto bytecode = ltn::c::assemble(instructions, link_info);
		const auto main_function = main_init.value_or("");

		reporter.may_throw();

		vm.setup(bytecode);
		auto x = vm.run(main_args.value_or({}), main_function);
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
