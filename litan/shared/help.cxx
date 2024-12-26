#include "help.hxx"
#include <iostream>

void print_usage_hint() {
	std::cout << "Usage:\n";
	std::cout << "    run   [options...] <script>   [args...] : Executes a script\n";
	std::cout << "    exec  [options...] <bytecode> [args...] : Executes precompiled bytecode\n";
	std::cout << "    build [options...] <script> <bytecode>  : Compiles script to bytecode\n";
	std::cout << "    dump  [options...] <script> <assembly>  : Compiles script to assembly for debugging and analysis\n";
}
