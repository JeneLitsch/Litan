#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <streambuf>
#include "Ltnc.hxx"
#include "LtnFileIO.hxx"

namespace ltnc {
	class CmdArgs {
	public:
		CmdArgs(int argc, char const *argv[]) {
			this->dstFile = argv[1];
			this->optimizationLevel = 0;
			this->silent = false;
			this->comments = false;
			for(unsigned idx = 2; idx < argc; idx++) {
				if(std::string(argv[idx]) == "-O0") {
					this->optimizationLevel = 0;
					continue;
				}
				if(std::string(argv[idx]) == "-o0") {
					this->optimizationLevel = 0;
					continue;
				}
				if(std::string(argv[idx]) == "-O") {
					this->optimizationLevel = 1;
					continue;
				}
				if(std::string(argv[idx]) == "-o") {
					this->optimizationLevel = 1;
					continue;
				}
				if(std::string(argv[idx]) == "-O1") {
					this->optimizationLevel = 1;
					continue;
				}
				if(std::string(argv[idx]) == "-o1") {
					this->optimizationLevel = 1;
					continue;
				}
				if(std::string(argv[idx]) == "-O2") {
					this->optimizationLevel = 2;
					continue;
				}
				if(std::string(argv[idx]) == "-o2") {
					this->optimizationLevel = 2;
					continue;
				}
				if(std::string(argv[idx]) == "-O3") {
					this->optimizationLevel = 3;
					continue;
				}
				if(std::string(argv[idx]) == "-o3") {
					this->optimizationLevel = 3;
					continue;
				}

				if(std::string(argv[idx]) == "-C") {
					this->comments = true;
					continue;
				}
				if(std::string(argv[idx]) == "-c") {
					this->comments = true;
					continue;
				}

				if(std::string(argv[idx]) == "-S") {
					this->silent = true;
					continue;
				}
				if(std::string(argv[idx]) == "-s") {
					this->silent = true;
					continue;
				}

				this->files.push_back(argv[idx]);
			}
		}

		unsigned getOptimizationLevel() const {
			return this->optimizationLevel;
		}

		bool getComments() const {
			return this->comments;
		}

		bool getSilent() const {
			return this->silent;
		}

		const std::vector<std::string> & getFiles() const {
			return this->files;
		}

		const std::string & getDstFile() const {
			return this->dstFile;
		}

	private:
		std::string dstFile;
		std::vector<std::string> files;
		unsigned optimizationLevel;
		bool comments;
		bool silent;
	};
}




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
		std::string asmb = ltnc.compile(
			source,
			ltnc::CompilerSettings(
				args.getComments(),
				args.getOptimizationLevel()),
			args.getSilent());
		ltn::writeFile(args.getDstFile(), asmb);
		return 0;
	}
	catch(std::runtime_error e) {
		std::cout << "[ERROR] " << e.what() << std::endl;
		std::cout << "\t>> Error while compiling" << std::endl;
		return 1;
	}
}
