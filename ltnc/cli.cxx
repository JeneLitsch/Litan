#include <iostream>
#include <fstream>
#include <filesystem>
#include "Ltnc.hxx"
#include "CompilerError.hxx"

int main(){
	const std::filesystem::path path = "example/example1.ltn"; 
	std::ifstream file(path);
	ltn::c::Ltnc compiler;
	try {
		compiler.compile(file, path);
	}
	catch(const ltn::c::CompilerError & error) {
		std::cout << error << "\n";
	}
}
