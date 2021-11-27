#include <fstream>
#include <filesystem>
#include "LtnVM.hxx"
#include "ltnvm/external/External.hxx"

class HelloWorld : public ltn::vm::ext::External {
public:
	HelloWorld() : External(0) {}
	virtual void operator()(ltn::vm::ext::Api &) override {
		std::cout << "Hello World\n";
	}
};

int main(int argc, char const *argv[]) {
	if(argc > 1) {
		if(std::filesystem::exists(argv[1])) {
			std::ifstream file(argv[1], std::ios::binary);
			std::vector<std::uint8_t> bytecode{
				std::istreambuf_iterator<char>(file),
				std::istreambuf_iterator<char>()
			};
			try {
				ltn::vm::LtnVM vm{std::cout};
				vm.registerExternal(42, std::make_unique<HelloWorld>());
				vm.setup(bytecode);
				vm.run();
				return EXIT_SUCCESS;
			}
			catch(const std::runtime_error & error) {
				std::cout << "[VM-Error] " << error.what() << "\n";
				return EXIT_FAILURE;
			}
		}
		std::cout << "[VM-Error] Cannot open: " << argv[1] << "\n";
	}
	std::cout << "[VM-Error] Needs a file to run\n";
	return EXIT_FAILURE;
}
