#pragma once
#include <vector>
#include <string>

namespace ltnc {
	class CmdArgs {
	public:
		CmdArgs(int argc, char const *argv[]);
		unsigned getOptimizationLevel() const;
		bool getComments() const;
		bool getSilent() const;
		const std::vector<std::string> & getFiles() const;
		const std::string & getDstFile() const;
	private:
		std::string dstFile;
		std::vector<std::string> files;
		unsigned optimizationLevel;
		bool comments;
		bool silent;
	};
}