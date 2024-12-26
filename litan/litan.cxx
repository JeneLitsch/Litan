#include <stdlib.h>
#include <iostream>
#include <vector>
#include <ranges>
#include <string_view>

#include "litan_core/args.hxx"
#include "litan_compiler/Ltnc.hxx"
#include "litan_vm/VM.hxx"
#include "litan_vm/utils/cast.hxx"
#include "litan_core/version.hxx"

#include "commands/run.hxx"
#include "commands/exec.hxx"
#include "commands/build.hxx"
#include "commands/dump.hxx"

void print_usage_hint() {
	std::cout << "Usage:\n";
	std::cout << "    run   [options...] <script>   [args...] : Executes a script\n";
	std::cout << "    exec  [options...] <bytecode> [args...] : Executes precompiled bytecode\n";
	std::cout << "    build [options...] <script> <bytecode>  : Compiles script to bytecode\n";
	std::cout << "    dump  [options...] <script> <assembly>  : Compiles script to assembly for debugging and analysis\n";
}

int main(int argc, const char** argv) {
	const std::vector<std::string_view> args_vector { argv + 1, argv + argc };
	std::span<const std::string_view> args = args_vector;
	try {
		if(args.empty()) {
			throw std::runtime_error{""};
		}

		std::span<const std::string_view> rest_args = args.subspan(1);

		const std::string_view secondary_command = args[0];
		if (secondary_command == "run") {
			return run(rest_args);
		}
		else if (secondary_command == "exec" && args.size() > 1) {
			return exec(rest_args);
		}
		else if (secondary_command == "build") {
			return build(rest_args);
		}
		else if (secondary_command == "dump") {
			return dump(rest_args);
		}
		else if (secondary_command == "help") {
			print_usage_hint();
			return EXIT_SUCCESS;
		}
		else {
			std::cout << "Invalid litan command " << secondary_command << ".\n";
			return EXIT_FAILURE;
		}
	}
	catch (const ltn::c::CompilerError & error) {
		std::cout << error << "\n";
		return EXIT_FAILURE;
	}
	catch (const std::exception & e) {
		std::cout << e.what() << "\n";
		std::cout << "Invalid litan command:\n";
		print_usage_hint();
		return EXIT_FAILURE;
	}
}
