#pragma once
#include <string>
namespace ltn::c {
	class IBufferObject {
	public:
		virtual std::string toString() const = 0;
	};
}