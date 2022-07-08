#include "Litan.hxx"
#include "ltnvm/cast.hxx"
#include "ltn/version.hxx"
#include <filesystem>
#include <fstream>
#include <iostream>
#include "ltn/args.hxx"


int main(int argc, char const *argv[]) {
	if(argc > 1) {
		if(ltn::print_version(argv[1])) {
			return 0;
		}
		ltn::c::Reporter reporter;
		ltn::LtnVm vm;
		try {
			stx::args::optional_list source_files {"-i"};
			stx::args::optional_list main_args {"--args"};

			stx::args::args{source_files, main_args}(argc, argv);

			std::vector<std::string> args;
			std::vector<ltn::c::Source> sources;
			for(const auto & source_file : source_files.get()) {
				sources.push_back(ltn::c::Source::make<std::ifstream>(
					std::string{source_file},
					std::string{source_file}
				));
			}

			auto program = ltn::c::parse(std::move(sources), reporter);
			const auto instructions = ltn::c::compile(program, reporter);
			reporter.may_throw();
			vm.setup(ltn::c::assemble(instructions));
			auto x = vm.run(main_args.get());
			std::cout << "Exit main() with return value: ";
			std::cout << ltn::vm::cast::to_string(x, vm.get_heap());
			std::cout << "\n";
		}
		catch (const ltn::c::CompilerError & error) {
			std::cout << error << "\n";
		}
		catch (const std::runtime_error & error) {
			std::cout << error.what() << "\n";
		}

		return EXIT_SUCCESS;
	}
	std::cout << "[Error] expected file and stdlib path";
	return EXIT_FAILURE;

}
