#include "LtnaInvalidMarker.hxx"

ltna::InvalidMarker::InvalidMarker(
	const std::string & msg,
	const std::string & inst,
	const std::string & marker,
	std::uint64_t lineNr)
:	AssemblerError(msg, inst, lineNr),
	marker(marker) {}