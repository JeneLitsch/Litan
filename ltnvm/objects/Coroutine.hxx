#pragma once
#include <vector>
#include "Object.hxx"
#include "ltnvm/Value.hxx"
#include "ltn/file/FunctionTable.hxx"

namespace ltn::vm {
	class Coroutine : public Object {
	public:
		constexpr static std::string_view typeName = "Coroutine";
		Coroutine() {}

		std::vector<Value> local_variables;
		const std::uint8_t * resume_address = nullptr;
		const FunctionTable::Entry * entry;
	};



	inline Coroutine clone(const Coroutine & clock) {
		return clock;
	}
}