#include <fstream>
#include "LtnVM.hxx"
int main(){
	std::ifstream file("example/example.bin.ltn", std::ios::binary);
	std::vector<std::uint8_t> bytecode{
		std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>()
	};
	ltn::vm::LtnVM vm{std::cout};
	vm.setup(bytecode);
	vm.run();
	return 0;
}
