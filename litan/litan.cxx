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


int main(int argc, const char** argv) {
	const std::vector<std::string_view> args_vector { argv + 1, argv + argc };
	std::span<const std::string_view> args = args_vector;
	if(!args.empty()) {
		try {
			const std::string_view secondary_command = args[0];
			if (secondary_command == "run" && args.size() > 1) {
				return run(args.subspan(1));
			}
			else if (secondary_command == "exec" && args.size() > 1) {
				return exec(args.subspan(1));
			}
			else if (secondary_command == "build" && args.size() > 2) {
				return build(args.subspan(1));
			}
			else if (secondary_command == "dump" && args.size() > 2) {
				return dump(args.subspan(1));
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
	}
	else {
		std::cout << "Expected litan command:\n";
		std::cout << "Usage:\n";
		std::cout << "    run     <script> args...    : Executes a script\n";
		std::cout << "    exec    <bytecode> args...  : Executes precompiled bytecode\n";
		std::cout << "    build   <script> <bytecode> : Compiles script to bytecode\n";
		std::cout << "    dump    <script> <assembly> : Compiles script to assembly for debugging and analysis\n";
		return EXIT_FAILURE;
	}
}
