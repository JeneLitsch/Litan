#include "Litan.hxx"
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
	if(argc > 2) {
		ltn::Ltnc compiler{std::make_unique<ltn::LtnBackend>()};
		ltn::Ltna assembler;
		ltn::LtnVm vm;
		try {
			std::filesystem::path stdlib = argv[1];
					
			for(const auto & stdFile : compiler.stdlib()) {
				const auto source = stdlib / stdFile; 
				compile_file(compiler, source);
			}
			std::vector<std::string> args;
			for(std::int64_t i = 2; i < argc; i++) {
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
			vm.setup(assembler.assemble(ss));
			vm.run(args);
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
