#include "CompilerError.hxx"
#include <sstream>
#include <iostream>

namespace ltn::c {
	namespace {
		std::string to_str(const std::string & msg, const SourceLocation & info) {
			std::stringstream ss;
			ss 	<< "[Litan Compiler Error] ";
			if(!info.sourcename.empty()) {
				ss << "\"" << info.sourcename << "\"" << " "; 
			}
			if(info.line) {
				ss	<< "line:" << info.line << " "; 
			}
			ss	<< msg;
			return ss.str();
		}
	}

	CompilerError::CompilerError(const std::string & msg, const SourceLocation & info)
		:	std::runtime_error(to_str(msg, info)) {}


	CompilerError::CompilerError(const std::string & msg)
		:	std::runtime_error(msg) {}

}