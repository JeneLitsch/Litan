#pragma once
#include "LtnaAssemblerError.hxx"
namespace ltna {
	class UnknownInstruction : public AssemblerError {
	public:
		UnknownInstruction(
			const std::string & inst,
			std::uint64_t lineNr);
	};
}