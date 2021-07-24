#pragma once
#include <string>
namespace ltnc {
	class CompilerSettings {
	public:
		CompilerSettings(bool comments, unsigned optimization, const std::string & stdlibPath);
		
		bool areCommentsActive() const;
		unsigned getOptimizationLevel() const;
		const std::string getStdlibPath() const;


	private:
		bool addComments = false;
		unsigned optimizations = 0;
		std::string stdlibPath;
	};
}