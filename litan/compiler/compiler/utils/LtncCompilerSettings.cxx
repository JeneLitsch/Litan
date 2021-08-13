#include "LtncCompilerSettings.hxx"

ltn::c::CompilerSettings::CompilerSettings(
	bool comments,
	unsigned optimizations,
	const std::string & stdlibPath) 
: 	addComments(comments),
	optimizations(optimizations),
	stdlibPath(stdlibPath) {}

bool ltn::c::CompilerSettings::areCommentsActive() const {
	return this->addComments;
}

unsigned ltn::c::CompilerSettings::getOptimizationLevel() const {
	return this->optimizations;
}

const std::string ltn::c::CompilerSettings::getStdlibPath() const {
	return this->stdlibPath;
}
