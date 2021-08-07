#pragma once
#include "LtnError.hxx"
namespace ltna {
	class AssemblerError : public ltn::Error {
	public:
		AssemblerError(
			const std::string & inst,
			std::uint64_t lineNr);

		AssemblerError(
			const std::string & inst);

		AssemblerError(
			const std::string & msg,
			const std::string & inst,
			std::uint64_t lineNr);

		std::uint64_t getLineNr() const;
	private:
		std::string inst;
		std::uint64_t lineNr;
	};
}