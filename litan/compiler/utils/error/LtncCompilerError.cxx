#include "LtncCompilerError.hxx"
#include <sstream>

std::string makeMessage(
	ltnc::ErrorCode errorCode,
	const std::string & msg,
	const ltnc::DebugInfo & debugInfo) {
	std::stringstream ss;
	ss << "Error(" << static_cast<unsigned>(errorCode) << ") at [";
	ss << debugInfo.lineNr << ":";
	ss << debugInfo.column << "]";
	if(debugInfo.inFunction) {
		ss << " in function ";
		ss << debugInfo.inFunction->ns;
		ss << debugInfo.inFunction->name; 
	}
	ss << " -> ";
	ss << msg;
	return ss.str();
}


ltnc::ErrorCode ltnc::CompilerError::getErrorCode() const {
	return this->errorCode;
}


ltnc::CompilerError::CompilerError(
	ErrorCode errorCode,
	const std::string & msg,
	const DebugInfo & debugInfo)
	: Error(makeMessage(errorCode, msg, debugInfo)),
	errorCode(errorCode) {}

