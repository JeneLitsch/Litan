#include <iostream>
#include <fstream>
#include <filesystem>
#include <string_view>
#include "ltnc/Ltnc.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/ast/Namespace.hxx"
#include "ltn/version.hxx"
#include "Args.hxx"



int main(int argc, char const *argv[]){
	if(argc > 1) {
		if(ltn::print_version(argv[1])) {
			return 0;
		}
	}
	try {
		const ltn::c::Args args{argv, static_cast<std::size_t>(argc)};

		std::vector<ltn::c::Source> sources;
		ltn::c::Reporter reporter;
		ltn::c::Config config;
		
		for(const auto & source_path : args.get_sources()) {
			sources.push_back(ltn::c::Source::make<std::fstream>(source_path, source_path));
		}

		const auto & target = args.get_target();
		std::cout << "[Target] " << target << "\n";
		std::ofstream ofile(target);
		if(!std::filesystem::exists(target)) {
			throw ltn::c::CompilerError{"Cannot open " + target.string(), {}};
		}
		auto program = ltn::c::parse(std::move(sources), config, reporter);
		if(args.is_set("-o")) {
			ltn::c::optimize(program);
		}
		auto instuctions = ltn::c::compile(program, config, reporter);
		if(args.is_set("-o")) {
			instuctions = ltn::c::peephole(instuctions);
		}
		auto bytecode = ltn::c::assemble(instuctions);
		for(auto byte : bytecode) {
			ofile << byte;
		}
		if(args.is_set("--asm")) {
			std::ofstream asm_file{std::filesystem::path{args.get_target()}.replace_extension(".asm")};
			asm_file << ltn::c::print(instuctions);
		}
		reporter.may_throw();
		std::cout << "Done!" << "\n";
	}
	catch(const ltn::c::CompilerError & error) {
		std::cout << error << "\n";
	}

}
