#include <fstream>
#include <filesystem>
#include "ltnvm/LtnVM.hxx"
#include "ltnvm/external/External.hxx"
#include "ltnvm/cast.hxx"

class Test : public ltn::vm::ext::External {
public:
	Test() : External(2) {}
	virtual void operator()(ltn::vm::ext::Api & api) override {
		const auto a = api.parameter<std::string>(0); 
		const auto b = api.parameter<std::string>(1); 
		std::cout << a << "|" << b << "\n";
		api.return_string("Hello World");
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
			std::vector<std::string> args;
			for(std::size_t i = 2; i < static_cast<std::size_t>(argc); ++i) {
				std::string_view arg = argv[i];
				if(arg.starts_with("%")) {
					arg.remove_prefix(1);
				}
				args.push_back(std::string{arg});
			}
			try {
				ltn::vm::LtnVM vm{std::cout};
				vm.register_external(42, std::make_unique<Test>());
				vm.setup(bytecode);
				auto x = vm.run(args);
				std::cout << "Exit main() with return value: ";
				std::cout << ltn::vm::cast::to_string(x, vm.get_heap());
				std::cout << "\n";
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
