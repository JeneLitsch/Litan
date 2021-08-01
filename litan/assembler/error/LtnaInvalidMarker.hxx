#pragma once
#include "LtnaAssemblerError.hxx"
namespace ltna {
	class InvalidMarker : public AssemblerError {
	public:
		std::string marker;

	protected:
		InvalidMarker(
			const std::string & msg,
			const std::string & inst,
			const std::string & marker,
			std::uint64_t lineNr);
	};
}