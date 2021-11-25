#include <iostream>
#include <fstream>
#include <filesystem>
#include "ltnc/Ltnc.hxx"
#include "ltnc/CompilerError.hxx"
#include "Args.hxx"
#include "ltnc/compile/LtnBackend.hxx"
#include "ltnc/ast/Namespace.hxx"
#include <string_view>


void compileFile(ltn::c::Ltnc & ltnc, const std::filesystem::path & filepath) {
	std::cout << "[Compiling] " << filepath << "\n";
	try {
		if(!std::filesystem::exists(filepath)) {
			throw ltn::c::CompilerError{"Cannot open " + filepath.string(), 0};
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
		
		for(const auto & stdFile : compiler.stdLib()) {
			const auto source = args.getStdLib() / stdFile; 
			compileFile(compiler, source);
		}

		for(const auto & source : args.getSources()) {
			compileFile(compiler, source);
		}

		const auto & target = args.getTarget();
		std::cout << "[Target] " << target << "\n";
		if(!std::filesystem::exists(target)) {
			throw ltn::c::CompilerError{"Cannot open " + target.string(), 0};
		}
		std::ofstream ofile(target);
		compiler.yield(ofile);
		std::cout << "Done!" << "\n";
	}
	catch(const ltn::c::CompilerError & error) {
		std::cout << error << "\n";
	}

}
