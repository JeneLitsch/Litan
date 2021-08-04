#pragma once
#include "LtncError.hxx"

namespace ltnc {
	namespace error {
		Error invalidToken(const DebugInfo & debugInfo, const std::string & token);
	}
}