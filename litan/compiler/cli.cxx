#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <streambuf>
#include "Ltnc.hxx"
#include "LtncCmdArgs.hxx"
#include "LtnFileIO.hxx"

int main(int argc, char const *argv[]) {
	if(argc < 2) {
		std::cout << "Args: <Source> <Flag> <Dest>" << std::endl;
		return 0;
	}

	ltnc::CmdArgs args(argc, argv);
	if(!args.getSilent()){

		std::cout << "Litan Compiler (c) Jene Litsch 2021" << std::endl;
		std::cout << "Flags: [";
		if(args.getOptimizationLevel()) {
			std::cout << "-O" << args.getOptimizationLevel() << " ";
		}
		if(args.getComments()) {
			std::cout << "-C ";
		}
		std::cout << "]" << std::endl;

		std::cout << "Src: [";
		for(const std::string & srcFile : args.getFiles()) {
			std::cout << srcFile << " ";
		}
		std::cout << "]" << std::endl;
		std::cout << "Dst: " << args.getDstFile() << std::endl;

	}
	std::string source;
	for(const std::string & srcFile : args.getFiles()) {
		source += ltn::readFile(srcFile);
	}
	try {
		ltnc::LTNC ltnc;
		std::string asmb = ltnc.compile(source, args.getComments(), args.getSilent(), args.getOptimizationLevel());
		ltn::writeFile(args.getDstFile(), asmb);
		return 0;
	}
	catch(std::runtime_error e) {
		std::cout << "[ERROR] " << e.what() << std::endl;
		std::cout << "\t>> Error while compiling" << std::endl;
		return 1;
	}
}
