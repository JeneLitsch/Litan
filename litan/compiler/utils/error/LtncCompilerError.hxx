#pragma once
#include "LtnError.hxx"
#include "LtncErrorCode.hxx"
#include "LtncDebugInfo.hxx"
namespace ltnc {
	class CompilerError : public ltn::Error {
	public:
		CompilerError(
			ErrorCode errorCode,
			const std::string & msg,
			const DebugInfo & debugInfo);

		ErrorCode getErrorCode() const;
	private:
		ErrorCode errorCode;
	};
}