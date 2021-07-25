#pragma once
#include <map>
#include "LtncAst.hxx"
#include "LtncCompilerSettings.hxx"
namespace ltnc {
	class Compiler {
	public:
		std::string compile(
			std::shared_ptr<Program> program,
			const CompilerSettings & settings);
	};
}