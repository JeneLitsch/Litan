#include "CompilerError.hxx"
#include <sstream>
#include <iostream>

namespace ltn::c {
	namespace {
		std::string to_str(const std::string & msg, const SourceLocation & context) {
			std::stringstream ss;
			ss 	<< "[Litan Compiler Error] ";
			if(!context.sourcename.empty()) {
				ss << "\"" << context.sourcename << "\"" << " "; 
			}
			if(context.line) {
				ss	<< "line:" << context.line << " "; 
			}
			ss	<< msg;
			return ss.str();
		}
	}



	CompilerError::CompilerError(const std::string & msg, const SourceLocation & context)
		:	std::runtime_error(to_str(msg, context)) {}



	CompilerError::CompilerError(const std::string & msg)
		:	std::runtime_error(msg) {}

}