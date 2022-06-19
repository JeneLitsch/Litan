#include "Litan.hxx"
#include "ltnvm/cast.hxx"
#include "ltn/version.hxx"
#include <filesystem>
#include <fstream>
#include <iostream>

void compile_file(ltn::c::Ltnc & ltnc, const std::filesystem::path & filepath) {
	std::cout << "[Compiling] " << filepath << "\n";
	try {
		if(!std::filesystem::exists(filepath)) {
			throw std::runtime_error{"Cannot open " + filepath.string()};
		}
		std::ifstream ifile(filepath);
		ltnc.compile(ifile, filepath);
	}
	catch(const std::runtime_error & error) {
		std::cout << error.what() << "\n";
	}
}

int main(int argc, char const *argv[]) {
	if(argc > 1) {
		if(ltn::print_version(argv[1])) {
			return 0;
		}
		ltn::Ltnc compiler{std::make_unique<ltn::LtnBackend>()};
		ltn::LtnVm vm;
		try {
			std::vector<std::string> args;
			for(std::int64_t i = 1; i < argc; i++) {
				std::string_view arg = argv[i];
				if(arg.starts_with("%")) {
					arg.remove_prefix(1);
					args.push_back(std::string{arg});
				} 
				else {
					compile_file(compiler, arg);
				}
			}
			std::stringstream ss;
			compiler.yield(ss);
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
