#include "CompilerError.hxx"
#include <sstream>

namespace {
	std::string to_str(const std::string & msg, std::size_t line) {
		std::stringstream ss;
		ss 	<< "[Litan Compiler Error] ";
		if(line) {
			ss	<< "line:" << line << " "; 
		}
		ss	<< msg;
		return ss.str();
	}
}

ltn::c::CompilerError::CompilerError(
	const std::string & msg,
	std::size_t line)
	:	std::runtime_error(to_str(msg, line)),
		line(line) {}