#pragma once
#include <vector>
#include "Object.hxx"
#include "ltnvm/Value.hxx"
#include "ltn/file/FunctionPool.hxx"

namespace ltn::vm {
	class Coroutine : public Object {
	public:
		virtual void stringify(VMCore & core, std::ostream & oss, bool nested) override;

		constexpr static std::string_view typeName = "Coroutine";
		Coroutine() {}

		std::vector<Value> local_variables;
		const std::uint8_t * resume_address = nullptr;
		const FunctionContext * context;
	};



	inline Coroutine clone(const Coroutine & clock) {
		return clock;
	}
}