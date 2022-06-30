#include "Litan.hxx"
#include "ltnvm/cast.hxx"
#include "ltn/version.hxx"
#include <filesystem>
#include <fstream>
#include <iostream>


int main(int argc, char const *argv[]) {
	if(argc > 1) {
		if(ltn::print_version(argv[1])) {
			return 0;
		}
		ltn::c::Reporter reporter;
		ltn::c::Config config;
		ltn::LtnVm vm;
		try {

			std::vector<std::string> args;
			std::vector<ltn::c::Source> sources;
			for(std::int64_t i = 1; i < argc; i++) {
				std::string_view arg = argv[i];
				if(arg.starts_with("%")) {
					arg.remove_prefix(1);
					args.push_back(std::string{arg});
				} 
				else {
					sources.push_back(ltn::c::Source::make<std::ifstream>(
						std::string{arg},
						std::string{arg}
					));
				}
			}

			auto program = ltn::c::to_ast(std::move(sources), config, reporter);

			std::stringstream ss { ltn::c::to_asm(program, config, reporter) };
			reporter.may_throw();
			vm.setup(ltn::a::assemble(ss));
			auto x = vm.run(args);
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
