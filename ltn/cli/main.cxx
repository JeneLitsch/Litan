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

	args.parse_options(desc);

	if(flag_version.is_set()) {
		std::cout << "Litan: " << ltn::version << "\n";
		return EXIT_SUCCESS;
	}
	if(flag_help.is_set()) {
		std::cout << desc.describe(); 
		return EXIT_SUCCESS;
	}
	
	flag_source.mandatory();
	
	ltn::c::Reporter reporter;
	ltn::LtnVm vm;
	try {
		std::vector<std::string> args;
		std::vector<ltn::c::Source> sources;
		for(const auto & source_file : flag_source.get()) {
			sources.push_back(ltn::c::Source::make<std::ifstream>(
				std::string{source_file},
				std::string{source_file}
			));
		}

		auto lexer = ltn::c::tokenize(std::move(sources), reporter);
		auto program = ltn::c::parse(lexer, reporter);
		if(flag_o.is_set()) ltn::c::optimize(program);
		auto instructions = ltn::c::compile(program, reporter);
		if(flag_o.is_set()) instructions = ltn::c::peephole(instructions);
		auto bytecode = ltn::c::assemble(instructions);

		reporter.may_throw();

		vm.setup(ltn::c::assemble(instructions));
		auto x = vm.run(main_args.get());
		std::cout << "Exit main() with return value: ";
		std::cout << ltn::vm::cast::to_string(x, vm.get_heap());
		std::cout << "\n";
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
