#include "LtncCompilerSettings.hxx"

ltnc::CompilerSettings::CompilerSettings(
	bool comments,
	unsigned optimizations,
	const std::string & stdlibPath) 
: 	addComments(comments),
	optimizations(optimizations),
	stdlibPath(stdlibPath) {}

bool ltnc::CompilerSettings::areCommentsActive() const {
	return this->addComments;
}

unsigned ltnc::CompilerSettings::getOptimizationLevel() const {
	return this->optimizations;
}

const std::string ltnc::CompilerSettings::getStdlibPath() const {
	return this->stdlibPath;
}
