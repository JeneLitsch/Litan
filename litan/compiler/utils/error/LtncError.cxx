#include "LtncError.hxx"
#include <sstream>

std::string makeMessage(
	ltn::c::ErrorCode errorCode,
	const std::string & msg,
	const ltn::c::DebugInfo & debugInfo) {
	std::stringstream ss;
	ss << "Error(" << static_cast<unsigned>(errorCode) << ") at [";
	ss << debugInfo.sourceName << ":";
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


ltn::c::ErrorCode ltn::c::Error::getErrorCode() const {
	return this->errorCode;
}


ltn::c::Error::Error(
	ErrorCode errorCode,
	const std::string & msg,
	const DebugInfo & debugInfo)
	: ltn::Error(makeMessage(errorCode, msg, debugInfo)),
	errorCode(errorCode) {}

