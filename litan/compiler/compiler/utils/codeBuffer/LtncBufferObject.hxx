#pragma once
#include <string>
namespace ltnc {
	class IBufferObject {
	public:
		virtual std::string toString() const = 0;
	};
}