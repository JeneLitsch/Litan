#include <iostream>
#include <fstream>
#include <filesystem>
#include "ltnc/Ltnc.hxx"
#include "ltnc/CompilerError.hxx"
#include "Args.hxx"
#include "ltnc/compile/LtnBackend.hxx"

int main(int argc, char const *argv[]){
	try {
		const ltn::c::Args args{argv, static_cast<std::size_t>(argc)};
		ltn::c::Ltnc compiler{std::make_unique<ltn::c::compile::LtnBackend>()};

		for(const auto & source : args.getSources()) {
			std::cout << "[Compiling] " << source << "\n";
			try {
				if(!std::filesystem::exists(source)) {
					throw ltn::c::CompilerError{"Cannot open " + source.string(), 0};
				}
				std::ifstream ifile(source);
				compiler.compile(ifile, source);
			}
			catch(const ltn::c::CompilerError & error) {
				std::cout << error << "\n";
			}
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
