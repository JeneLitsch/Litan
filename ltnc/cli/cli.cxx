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
		auto program = ltn::c::to_ast(std::move(sources), config, reporter);
		if(args.is_set("-o")) {
			ltn::c::optimize::optimize(program);
		}
		ofile << ltn::c::to_asm(program, config, reporter);
		reporter.may_throw();
		std::cout << "Done!" << "\n";
	}
	catch(const ltn::c::CompilerError & error) {
		std::cout << error << "\n";
	}

}
