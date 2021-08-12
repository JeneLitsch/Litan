#pragma once
#include <map>
#include "LtncAst.hxx"
#include "LtncCompilerSettings.hxx"
#include "LtnErrorReporter.hxx"
namespace ltnc {
	class Compiler {
	public:
		std::string compile(
			const Program & program,
			ltn::ErrorReporter & error,
			const CompilerSettings & settings);
	};
}