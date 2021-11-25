#include <fstream>
#include <filesystem>
#include "LtnVM.hxx"
int main(int argc, char const *argv[]) {
	if(argc > 1) {
		if(std::filesystem::exists(argv[1])) {
			std::ifstream file(argv[1], std::ios::binary);
			std::vector<std::uint8_t> bytecode{
				std::istreambuf_iterator<char>(file),
				std::istreambuf_iterator<char>()
			};
			ltn::vm::LtnVM vm{std::cout};
			vm.setup(bytecode);
			vm.run();
			return EXIT_SUCCESS;
		}
		std::cout << "[VM-Error] Cannot open: " << argv[1] << "\n";
	}
	std::cout << "[VM-Error] Needs a file to run\n";
	return EXIT_FAILURE;
}
