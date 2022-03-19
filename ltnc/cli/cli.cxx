#include <iostream>
#include <fstream>
#include <filesystem>
#include "ltnc_core/Ltnc.hxx"
#include "ltnc_core/CompilerError.hxx"
#include "Args.hxx"
#include "ltnc/compile/LtnBackend.hxx"
#include "ltnc_core/ast/Namespace.hxx"
#include <string_view>


void compile_file(ltn::c::Ltnc & ltnc, const std::filesystem::path & filepath) {
	std::cout << "[Compiling] " << filepath << "\n";
	try {
		if(!std::filesystem::exists(filepath)) {
			throw ltn::c::CompilerError{"Cannot open " + filepath.string(), {}};
		}
		std::ifstream ifile(filepath);
		ltnc.compile(ifile, filepath);
	}
	catch(const ltn::c::CompilerError & error) {
		std::cout << error << "\n";
	}
}

int main(int argc, char const *argv[]){
	try {
		const ltn::c::Args args{argv, static_cast<std::size_t>(argc)};
		ltn::c::Ltnc compiler{std::make_unique<ltn::c::compile::LtnBackend>()};
		
		for(const auto & stdFile : compiler.stdlib()) {
			const auto source = args.get_stdlib() / stdFile; 
			compile_file(compiler, source);
		}

		for(const auto & source : args.get_sources()) {
			compile_file(compiler, source);
		}

		const auto & target = args.get_target();
		std::cout << "[Target] " << target << "\n";
		std::ofstream ofile(target);
		if(!std::filesystem::exists(target)) {
			throw ltn::c::CompilerError{"Cannot open " + target.string(), {}};
		}
		compiler.yield(ofile);
		std::cout << "Done!" << "\n";
	}
	catch(const ltn::c::CompilerError & error) {
		std::cout << error << "\n";
	}

}
