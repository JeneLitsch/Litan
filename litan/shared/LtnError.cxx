#include "LtnError.hxx"


std::ostream & ltn::operator<<(
	std::ostream & stream,
	const ltn::Error & error) {
	stream << error.str();
	return stream;
}