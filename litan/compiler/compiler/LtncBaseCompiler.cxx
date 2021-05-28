#include "LtncBaseCompiler.hxx"

std::string ltnc::BaseCompiler::pushToStack(const unsigned amount) const {
	return "raise_stack_ptr " + std::to_string(amount) + "\n";
}

std::string ltnc::BaseCompiler::popFromStack(const unsigned amount) const {
	return "lower_stack_ptr " + std::to_string(amount) + "\n";
}

void ltnc::BaseCompiler::activateComments(bool active) {
	this->addComments = active;
}

void ltnc::BaseCompiler::setOptimization(unsigned active) {
	this->optimizations = active;
}

unsigned ltnc::BaseCompiler::getOptimizationLevel() const {
	return this->optimizations;
}

std::string ltnc::BaseCompiler::comment(const std::string & content) const {
	if(this->addComments) {
		return "// " + content + "\n";
	}
	else{
		return "";
	}
}
