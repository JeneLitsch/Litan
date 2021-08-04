#pragma once
#include "LtnError.hxx"
#include "LtncErrorCode.hxx"
#include "LtncDebugInfo.hxx"
namespace ltnc {
	class Error : public ltn::Error {
	public:
		Error(
			ErrorCode errorCode,
			const std::string & msg,
			const DebugInfo & debugInfo);

		ErrorCode getErrorCode() const;
	private:
		ErrorCode errorCode;
	};
}