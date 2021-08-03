#include "LtncCompilerError.hxx"
#include <sstream>

std::string makeMessageHeader(
	ltnc::ErrorCode errorCode,
	const ltnc::TokenDebugInfo & debugInfo) {
	std::stringstream ss;
	ss << "Error(" << static_cast<unsigned>(errorCode) << ") at [";
	ss << debugInfo.lineNr << ":";
	ss << debugInfo.column << "]";
	return ss.str();
}


std::string makeMessage(
	ltnc::ErrorCode errorCode,
	const std::string & msg,
	const ltnc::NodeDebugInfo & debugInfo) {
	std::stringstream ss;
	ss << makeMessageHeader(errorCode, debugInfo.tokenInfo);
	ss << debugInfo.inFunction.ns;
	ss << debugInfo.inFunction.name; 
	ss << " -> ";
	ss << msg;
	return ss.str();
}


std::string makeMessage(
	ltnc::ErrorCode errorCode,
	const std::string & msg,
	const ltnc::TokenDebugInfo & debugInfo) {
	std::stringstream ss;
	ss << makeMessageHeader(errorCode, debugInfo);
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
	const NodeDebugInfo & debugInfo)
	: Error(makeMessage(errorCode, msg, debugInfo)),
	errorCode(errorCode) {}


ltnc::CompilerError::CompilerError(
	ErrorCode errorCode,
	const std::string & msg,
	const TokenDebugInfo & debugInfo)
	: Error(makeMessage(errorCode, msg, debugInfo)),
	errorCode(errorCode) {}
