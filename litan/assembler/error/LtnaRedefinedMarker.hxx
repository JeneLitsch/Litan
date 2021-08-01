#pragma once
#include "LtnaInvalidMarker.hxx"
namespace ltna {
	class RedefinedMarker : public InvalidMarker {
	public:
		RedefinedMarker(const std::string & marker);
	};
}