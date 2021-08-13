#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <streambuf>
#include "Ltnc.hxx"
#include "LtnFileIO.hxx"
#include "LtnError.hxx"

namespace ltn::c {
	class CmdArgs {
	public:
		CmdArgs(int argc, char const *argv[]) {
			this->dstFile = argv[1];
			this->optimizationLevel = 0;
			this->silent = false;
			this->comments = false;
			for(int idx = 2; idx < argc; idx++) {
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

				if(std::string(argv[idx]) == "-P") {
					this->print = true;
					continue;
				}
				if(std::string(argv[idx]) == "-p") {
					this->print = true;
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

		bool getPrint() const {
			return this->print;
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
		bool print;
	};
}




int main(int argc, char const *argv[]) {
	if(argc < 2) {
		std::cout << "Args: <Source> <Flag> <Dest>" << std::endl;
		return 0;
	}

	ltn::c::CmdArgs args(argc, argv);
	if(!args.getSilent()){

		std::cout << "Litan Compiler (c) Jene Litsch 2021" << std::endl;
		std::cout << "Flags: [ ";
		if(args.getOptimizationLevel()) {
			std::cout << "-o" << args.getOptimizationLevel() << " ";
		}
		if(args.getComments()) {
			std::cout << "-c ";
		}
		if(args.getPrint()) {
			std::cout << "-p ";
		}
		std::cout << "]" << std::endl;

		std::cout << "Src: [";
		for(const std::string & srcFile : args.getFiles()) {
			std::cout << srcFile << " ";
		}
		std::cout << "]" << std::endl;
		std::cout << "Dst: " << args.getDstFile() << std::endl;

	}
	std::vector<ltn::c::Ltnc::SourcePair> sources;
	for(const std::string & srcFile : args.getFiles()) {
		sources.push_back({srcFile, ltn::readFile(srcFile)});
	}
	try {
		ltn::c::Ltnc ltnc;
		ltn::c::CompilerSettings settings(
			args.getComments(),
			args.getOptimizationLevel(),
			"stdlib");
		std::string asmb = ltnc.compile(
			sources,
			settings,
			args.getSilent(),
			args.getPrint());
		ltn::writeFile(args.getDstFile(), asmb);
		return 0;
	}
	catch(const ltn::Error & error) {
		std::cout << error << std::endl;
		std::cout << std::endl;
		return 1;
	}
}
