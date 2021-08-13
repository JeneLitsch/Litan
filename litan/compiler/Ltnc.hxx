#pragma once
#include <string>
#include <vector>
#include "LtncCompilerSettings.hxx"
namespace ltn::c {
	class Ltnc {
	public:
		struct SourcePair {
			std::string sourceName;
			std::string source;
		};
		std::string compile(
			const std::vector<SourcePair> & sources,
			const CompilerSettings & settings,
			bool silent,
			bool print) const;
	private:
	};
}