#pragma once
#include <vector>
#include "Object.hxx"
#include "ltnvm/Value.hxx"

namespace ltn::vm {
	class CoRoutine : public Object {
	public:
		constexpr static std::string_view typeName = "CoRoutine";
		CoRoutine() {}

		std::vector<Value> local_variables;
		const std::uint8_t * resume_address = nullptr;
	};



	inline CoRoutine clone(const CoRoutine & clock) {
		return clock;
	}
}