#pragma once
#include <string>
#include "LtncCompilerSettings.hxx"
namespace ltnc {
	class LTNC {
	public:
		std::string compile(
			const std::string & source,
			const CompilerSettings & settings,
			bool silent) const;
	private:
	};
}