#pragma once
#include "LtnaInvalidMarker.hxx"
namespace ltn::a {
	class UnknownMarker : public InvalidMarker {
	public:
		UnknownMarker(const std::string & marker);
	};
}