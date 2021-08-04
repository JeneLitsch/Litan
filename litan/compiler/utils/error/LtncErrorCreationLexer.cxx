#include "LtncErrorCreationLexer.hxx"

namespace ltnc {
	Error error::invalidToken(const DebugInfo & debugInfo, const std::string & token) {
		return Error(ErrorCode::INVALID_TOKEN, "Invalid Token: " + token, debugInfo);
	}
}


