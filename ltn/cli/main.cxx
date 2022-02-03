#include "Litan.hxx"
#include <filesystem>
#include <fstream>

void compileFile(ltn::c::Ltnc & ltnc, const std::filesystem::path & filepath) {
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

		std::filesystem::path stdlib = argv[argc-1];
				
		for(const auto & stdFile : compiler.stdLib()) {
			const auto source = stdlib / stdFile; 
			compileFile(compiler, source);
		}
		
		for(std::int64_t i = 1; i+1 < argc; i++) {
			compileFile(compiler, argv[i]);
		}
		std::stringstream ss;
		compiler.yield(ss);
		vm.setup(assembler.assemble(ss));
		vm.run();
		return EXIT_SUCCESS;
	}
	std::cout << "[Error] expected file and stdlib path";
	return EXIT_FAILURE;

}
