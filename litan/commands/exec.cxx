#include "exec.hxx"
#include "stdlib.h"
#include "litan_vm/litan_vm.hxx"
#include "litan/shared/options.hxx"
#include "litan/shared/help.hxx"
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
	ExecOptions options = parse_options<ExecOptions, read_exec_option>(flags);

	if(options.help) {
		print_usage_hint();
		return EXIT_SUCCESS;
	}

	if(rest.size() < 1) {
		throw std::runtime_error{"Invalid exec arguments"};
	}

	std::string_view bytecode_path = rest[0];
	std::span<const std::string_view> script_args = rest.subspan(1);
	auto bytecode = read_bytecode(bytecode_path);
	const auto main_function = "";
	std::vector<ltn::Any> main_args;
	for (const auto & arg : script_args) {
		main_args.push_back(ltn::Any(arg));
	}
	auto vm = ltn::vm::load(bytecode);
	ltn::vm::execute(vm, main_function, main_args);
	return EXIT_SUCCESS;
}