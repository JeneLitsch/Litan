#pragma once
#include "LtncError.hxx"

namespace ltn::c {
	namespace error {
		Error invalidToken(const DebugInfo & debugInfo, const std::string & token);
	}
}