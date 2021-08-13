#pragma once
#include "LtnaInvalidMarker.hxx"
namespace ltn::a {
	class RedefinedMarker : public InvalidMarker {
	public:
		RedefinedMarker(const std::string & marker);
	};
}