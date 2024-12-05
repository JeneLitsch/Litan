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


std::ofstream open_target(const std::filesystem::path & path, std::ios::openmode openmode = std::ios::binary) {
	const auto dir = path.parent_path();
	if(!std::filesystem::exists(dir) && !std::filesystem::create_directory(dir)) {
		std::ostringstream oss;
		oss << "Directory " << dir << " does not exist and cannot be created.";
		throw ltn::c::CompilerError { oss.str() };
	}

	std::ofstream ofile { path, openmode };
	if(!ofile) {
		std::ostringstream oss;
		oss << "Cannot open target " << path; 
		throw ltn::c::CompilerError { oss.str() };
	}

	return ofile;
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



std::vector<std::uint8_t> build(std::string_view script_path) {
	auto sources = ltn::c::read_sources({script_path});
	auto source = ltn::c::parse(sources);
	auto program = ltn::c::analyze(source);
	ltn::c::optimize(program);
	auto instructions = ltn::c::compile(program);
	instructions = ltn::c::peephole(instructions);
	auto link_info = ltn::c::link(program, instructions);
	auto bytecode = ltn::c::assemble(instructions, link_info);
	return bytecode;
}



int run(std::string_view script_path, std::span<const std::string_view> script_args) {
	auto bytecode = build(script_path); 
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



int compile(std::string_view script_path, std::string_view target_path) {
	auto bytecode = build(script_path);
	std::cout << "Compiling script...\n";
	auto ofile = open_target(target_path);
	std::cout << "[Source] " << script_path << "\n";
	std::cout << "[Target] " << target_path << "\n";
	for(std::uint8_t byte : bytecode) {
		ofile << byte;
	}
	std::cout << "Done!\n";
	return EXIT_SUCCESS;
}


int exec(std::string_view bytecode_path, std::span<const std::string_view> script_args) {
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



int preview(std::string_view script_path, std::string_view target_path) {
	auto sources = ltn::c::read_sources({script_path});
	auto source = ltn::c::parse(sources);
	auto program = ltn::c::analyze(source);
	ltn::c::optimize(program);
	auto instructions = ltn::c::compile(program);
	instructions = ltn::c::peephole(instructions);
	auto ofile = open_target(target_path, std::ios::openmode(0));
	ofile << ltn::c::print(instructions);
	return EXIT_SUCCESS;
}



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
