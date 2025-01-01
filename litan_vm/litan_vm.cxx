#include "litan_vm.hxx"
#include "VM.hxx"

namespace ltn::vm {
	VM load(std::span<std::uint8_t> bytecode) {
		VM vm;
		vm.setup(bytecode);
		return vm;
	}


	ltn::Any execute(VM & vm, const std::string & function_name, const std::vector<ltn::Any> & arguments) {
		return vm.call(function_name, arguments);
	}
}