#include "exec.hxx"
#include "stdlib.h"
#include "litan_vm/VM.hxx"
#include "litan/shared/options.hxx"
#include "litan/shared/file.hxx"

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



int exec(std::span<const std::string_view> args) {
	std::span<const std::string_view> flags = cut_options(args);
	std::span<const std::string_view> rest = args.subspan(flags.size());
	BuildOptions options = parse_options<BuildOptions, read_build_option>(flags);

	if(rest.size() < 1) {
		throw std::runtime_error{"Invalid exec arguments"};
	}

	std::string_view bytecode_path = rest[0];
	std::span<const std::string_view> script_args = rest.subspan(1);
	auto bytecode = read_bytecode(bytecode_path);
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