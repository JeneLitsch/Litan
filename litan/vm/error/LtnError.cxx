#include "LtnError.hxx"

ltn::Error::Error(const std::string & msg)
	: std::runtime_error(msg) {}

ltn::Error::Error()
	: std::runtime_error("An error occured during runtime") {}