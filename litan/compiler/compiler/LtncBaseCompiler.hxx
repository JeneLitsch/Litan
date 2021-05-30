#pragma once
#include <string>
#include "LtncCompilerPack.hxx"
namespace ltnc {
	class BaseCompiler {
	protected:
		std::string pushToStack(const unsigned amount) const;
		std::string popFromStack(const unsigned amount) const;
		std::string comment(const CompilerPack & compPkg, const std::string & content) const;

	};
}