#include <stdlib.h>
#include <iostream>
#include <vector>
#include <ranges>
#include <string_view>

#include "ltn/args.hxx"
#include "ltnc/Ltnc.hxx"
#include "ltnvm/VM.hxx"
#include "ltnvm/utils/cast.hxx"
#include "ltn/version.hxx"

#include "commands/run.hxx"
#include "commands/exec.hxx"
#include "commands/compile.hxx"
#include "commands/preview.hxx"


int main(int argc, const char** argv) {
	const std::vector<std::string_view> args_vector { argv + 1, argv + argc };
	std::span<const std::string_view> args = args_vector;
	if(!args.empty()) {
		try {
			const std::string_view secondary_command = args[0];
			if (secondary_command == "run" && args.size() > 1) {
				return run(args[1], args.subspan(2));
			}
			else if (secondary_command == "exec" && args.size() > 1) {
				return exec(args[1], args.subspan(2));
			}
			else if (secondary_command == "compile" && args.size() > 2) {
				return compile(args[1], args[2]);
			}
			else if (secondary_command == "preview" && args.size() > 2) {
				return preview(args[1], args[2]);
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
		std::cout << "    compile <script> <bytecode> : Compiles script to bytecode\n";
		std::cout << "    preview <script> <assembly> : Compiles script to assembly for debugging and analysis\n";
		return EXIT_FAILURE;
	}
}
