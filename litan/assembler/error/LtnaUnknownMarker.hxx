#pragma once
#include "LtnaInvalidMarker.hxx"
namespace ltna {
	class UnknownMarker : public InvalidMarker {
	public:
		UnknownMarker(const std::string & marker);
	};
}