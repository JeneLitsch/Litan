#include "LtncCompilerSettings.hxx"

ltnc::CompilerSettings::CompilerSettings(bool comments, unsigned optimizations) 
	: addComments(comments), optimizations(optimizations) {}

bool ltnc::CompilerSettings::areCommentsActive() const {
	return this->addComments;
}

unsigned ltnc::CompilerSettings::getOptimizationLevel() const {
	return this->optimizations;
}