#include <iostream>
#include <fstream>
#include <filesystem>
#include <string_view>
#include "ltnc/Ltnc.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/ast/Namespace.hxx"
#include "ltn/version.hxx"
#include "Args.hxx"
#include "ltn/args.hxx"

std::vector<ltn::c::Source> read_sources(const auto & filepaths, ltn::c::Reporter & reporter) {
	std::vector<ltn::c::Source> sources;
	for(const auto & source_path : filepaths) {
		if(auto source = ltn::c::Source::make<std::fstream>(source_path, source_path)) {
			sources.push_back(std::move(source));
		}
		else {
			std::ostringstream oss;
			oss << "Cannot open source " << source_path;
			reporter << ltn::c::CompilerError { oss.str() };
		}
	}
	return sources;
}



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
	const auto asm_path = std::filesystem::path{target} .replace_extension(".asm");
	std::ofstream asm_file { asm_path };
	asm_file << ltn::c::print(instructions);
}



int main(int argc, char const *argv[]){
	if(argc > 1) {
		if(ltn::print_version(argv[1])) {
			return 0;
		}
	}
	try {
		stx::args::options options{std::array{"-o", "--asm"}};
		stx::args::mandatory target;
		stx::args::optional_list source_files{"-i"};

		stx::args::args{ options, target, source_files } (argc, argv);

		ltn::c::Reporter reporter;

		auto sources = read_sources(source_files.get(), reporter);
		auto ofile = open_target(target.get(), reporter);
		
		auto program = ltn::c::parse(std::move(sources), reporter);
		if(options.is_set("-o")) ltn::c::optimize(program);
		auto instructions = ltn::c::compile(program, reporter);
		if(options.is_set("-o")) instructions = ltn::c::peephole(instructions);
		auto bytecode = ltn::c::assemble(instructions);

		reporter.may_throw();
		for(auto byte : bytecode) {
			ofile << byte;
		}
		if(options.is_set("--asm")) output_asm(target.get(), instructions);
		std::cout << "Done!" << "\n";
		return EXIT_SUCCESS;
	}
	catch(const ltn::c::CompilerError & error) {
		std::cout << error << "\n";
		return EXIT_FAILURE;
	}

}
