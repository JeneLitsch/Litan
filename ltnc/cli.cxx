#include <iostream>
#include <fstream>
#include <filesystem>
#include "Ltnc.hxx"
#include "CompilerError.hxx"

int main(){
	const std::filesystem::path ipath = "example/example1.ltn"; 
	const std::filesystem::path opath = "example/example1.asm.ltn"; 
	std::ifstream ifile(ipath);
	std::ofstream ofile(opath);
	ltn::c::Ltnc compiler;
	try {
		compiler.compile(ifile, ipath);
		compiler.yield(ofile);
	}
	catch(const ltn::c::CompilerError & error) {
		std::cout << error << "\n";
	}
}
