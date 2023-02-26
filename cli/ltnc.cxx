#include <iostream>
#include <fstream>
#include <filesystem>
#include <string_view>
#include "ltnc/Ltnc.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/Namespace.hxx"
#include "ltn/version.hxx"
#include "ltn/args.hxx"
#include "stdxx/args.hxx"


std::ofstream open_target(
	const std::filesystem::path & path,
	ltn::c::Reporter & reporter) {
	
	const auto dir = path.parent_path();

	if(!std::filesystem::exists(dir) && !std::filesystem::create_directory(dir)) {
		std::ostringstream oss;
		oss << "Directory " << dir << " does not exist and cannot be created.";
		reporter << ltn::c::CompilerError { oss.str() };
	}

	std::ofstream ofile { path, std::ios::binary };
	if(!ofile) {
		std::ostringstream oss;
		oss << "Cannot open target " << path; 
		reporter << ltn::c::CompilerError { oss.str() };
	}

	std::cout << "[Target] " << path << "\n";

	return ofile;
}



void output_asm(const std::filesystem::path & target, const auto & instructions) {
	std::ofstream asm_file { target };
	asm_file << ltn::c::print(instructions);
}



int main(int argc, char const *argv[]){
	stx::args args { argc, argv };

	stx::option_description desc {
		"Litan Compiler [ltnc] " + std::string(ltn::version),
		"The Litan Compiler takes a number of Litan files and compiles them to an executable bytecode file for ltnvm." };

	auto & flag_o = desc.add<stx::option_flag>(
		{"-o"},
		"Optimization",
		"If this flag is set the compiler applies optimizations to the code");

	auto & flag_asm = desc.add<stx::option_string>(
		{"--asm"},
		"File for assembly output",
		"Use this option to generate human readable assembly code for debugging. The assembly code will be stored in sepcified file"
	);

	auto & flag_version = ltn::args::version(desc);
	auto & flag_help    = ltn::args::help(desc);

	auto & flag_exe = desc.add<stx::option_string>(
		{"--exe"},
		"Executable Bytecode",
		"Specifies the output file for executable bytecode."
	);

	auto & flag_source = desc.add<stx::option_string_list>(
		{"--src"},
		"Source",
		"Specifies a list of source files to compile."
	);

	args.parse_options(desc);

	if(flag_version) {
		std::cout << "Litan: " << ltn::version << "\n";
		return EXIT_SUCCESS;
	}
	if(flag_help) {
		std::cout << desc.describe(); 
		return EXIT_SUCCESS;
	}

	flag_source.mandatory();

	try {
		ltn::c::Reporter reporter;
		auto sources = ltn::c::read_sources(flag_source.value(), reporter);
		auto tokens = ltn::c::lex(sources, reporter);
		auto source = ltn::c::parse(tokens, reporter);
		auto program = ltn::c::analyze(source, reporter);
		if(flag_o) ltn::c::optimize(program);
		auto [instructions, link_info] = ltn::c::compile(program, reporter);
		if(flag_o) instructions = ltn::c::peephole(instructions);
		reporter.may_throw();
		if(flag_asm) {
			output_asm(flag_asm.value(), instructions);
		}
		auto bytecode = ltn::c::assemble(instructions, link_info);

		if(flag_exe) {
			auto ofile = open_target(flag_exe.value(), reporter);
			for(auto byte : bytecode) {
				ofile << byte;
			}
		}
		
		
		std::cout << "Done!" << "\n";
		return EXIT_SUCCESS;
	}
	catch(const ltn::c::CompilerError & error) {
		std::cout << error << "\n";
		return EXIT_FAILURE;
	}

}
