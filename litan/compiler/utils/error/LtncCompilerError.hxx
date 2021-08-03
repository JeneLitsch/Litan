#pragma once
#include "LtnError.hxx"
#include "LtncErrorCode.hxx"
#include "LtncNodeDebugInfo.hxx"
namespace ltnc {
	class CompilerError : public ltn::Error {
	public:
		CompilerError(
			ErrorCode errorCode,
			const std::string & msg,
			const NodeDebugInfo & debugInfo);

		CompilerError(
			ErrorCode errorCode,
			const std::string & msg,
			const TokenDebugInfo & debugInfo);

		ErrorCode getErrorCode() const;
	private:
		ErrorCode errorCode;
	};
}