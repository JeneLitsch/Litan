#include "LtncCmdArgs.hxx"

ltnc::CmdArgs::CmdArgs(int argc, char const *argv[]) {
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

unsigned ltnc::CmdArgs::getOptimizationLevel() const {
	return this->optimizationLevel;
}

bool ltnc::CmdArgs::getComments() const {
	return this->comments;
}

bool ltnc::CmdArgs::getSilent() const {
	return this->silent;
}

const std::vector<std::string> & ltnc::CmdArgs::getFiles() const {
	return this->files;
}

const std::string & ltnc::CmdArgs::getDstFile() const {
	return this->dstFile;
}
