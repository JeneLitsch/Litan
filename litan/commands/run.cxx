#include "run.hxx"
#include "../shared/shared.hxx"
#include "../shared/file.hxx"
#include "litan_vm/VM.hxx"

int run(std::span<const std::string_view> args) {
	std::string_view script_path = args[0];
	std::span<const std::string_view> script_args = args.subspan(1);
	std::cout << script_args.size() << "\n";

	auto sst = analysis_phase(script_path);
	auto instructions = synthesis_phase(sst);
	auto link_info = ltn::c::link(sst, instructions);
	auto bytecode = ltn::c::assemble(instructions, link_info);

	const auto main_function = "";
	ltn::vm::VM vm;
	vm.setup(bytecode);
	std::vector<ltn::Any> main_args;
	for (const auto & arg : script_args) {
		main_args.push_back(ltn::Any(arg));
	}
	vm.call(main_function, main_args);
	return EXIT_SUCCESS;
}