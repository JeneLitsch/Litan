#include <fstream>
#include <filesystem>
#include "ltnvm/VM.hxx"
#include "ltnvm/utils/cast.hxx"
#include "ltn/version.hxx"
#include "ltn/args.hxx"
#include "stdxx/args.hxx"


std::vector<ltn::Any> args_str_to_any(const std::vector<std::string> & strings) {
	std::vector<ltn::Any> anys;
	std::ranges::transform(strings, std::back_inserter(anys), ltn::Any::from_string);
	return anys;
}


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
	stx::args args {argc, argv};

	stx::option_description desc {
		"Litan Virtual Machine [ltnvm] " + std::string{ltn::version},
		"The Litan VM executes an previous compiled Litan bytecode file."
	};

	auto & exec = desc.add<stx::option_string>(
		{"--exe"},
		"Executable Bytecode",
		"Path to an executable Litan bytecode file");

	auto & flag_version = ltn::args::version(desc);
	auto & flag_help    = ltn::args::help(desc);
	auto & main_args    = ltn::args::main_args(desc);
	auto & main_init    = ltn::args::main_init(desc);

	args.parse_options(desc);

	if(flag_version) {
		std::cout << "Litan: " << ltn::version << "\n";
		return EXIT_SUCCESS;
	}
	if(flag_help) {
		std::cout << desc.describe(); 
		return EXIT_SUCCESS;
	}

	exec.mandatory();

	try {
		const auto bytecode = read_bytecode(exec.value());

		ltn::vm::VM vm;
		const auto main_function = main_init.value_or("");
		vm.setup(bytecode);
		auto x = vm.call(main_function, args_str_to_any(main_args.value_or({})));
		std::cout << "Exit main() with return value: " << x << "\n";		
		return EXIT_SUCCESS;
	}
	catch(const std::runtime_error & error) {
		std::cout << "[VM-Error] " << error.what() << "\n";
		return EXIT_FAILURE;
	}
}
