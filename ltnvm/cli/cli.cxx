#include <fstream>
#include <filesystem>
#include "ltnvm/LtnVM.hxx"
#include "ltnvm/external/External.hxx"
#include "ltnvm/cast.hxx"
#include "ltn/version.hxx"
#include "ltn/args.hxx"


std::vector<std::uint8_t> read_bytecode(const std::filesystem::path & path) {
	std::ifstream file(path, std::ios::binary);
	if(!file) {
		std::ostringstream oss;
		oss << "Cannot open " << path; 
		throw std::runtime_error { oss.str() }; 
	}
	return std::vector<std::uint8_t> {
		std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>()
	};
}


int main(int argc, char const *argv[]) {
	if(argc <= 1) {
		std::cerr << "[VM-Error] Needs a file to run\n";
		return EXIT_FAILURE;
	}

	if(ltn::print_version(argv[1])) return EXIT_SUCCESS;

	try {
		stx::args::mandatory binary_file;
		stx::args::optional_list main_args { "--args" };
		stx::args::args { binary_file, main_args } (argc, argv);

		const auto bytecode = read_bytecode(binary_file.get());

		ltn::vm::LtnVM vm;
		vm.setup(bytecode);
		auto x = vm.run(main_args.get());
		std::cout
			<< "Exit main() with return value: "
			<< ltn::vm::cast::to_string(x, vm.get_heap())
			<< "\n";
		
		return EXIT_SUCCESS;
	}
	catch(const std::runtime_error & error) {
		std::cout << "[VM-Error] " << error.what() << "\n";
		return EXIT_FAILURE;
	}
}
