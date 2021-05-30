#include "LtncBaseCompiler.hxx"

std::string ltnc::BaseCompiler::pushToStack(const unsigned amount) const {
	return "raise_stack_ptr " + std::to_string(amount) + "\n";
}

std::string ltnc::BaseCompiler::popFromStack(const unsigned amount) const {
	return "lower_stack_ptr " + std::to_string(amount) + "\n";
}

std::string ltnc::BaseCompiler::comment(const CompilerPack & compPkg, const std::string & content) const {
	if(compPkg.getSettings().areCommentsActive()) {
		return "// " + content + "\n";
	}
	else{
		return "";
	}
}
