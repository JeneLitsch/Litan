#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include "stdxx/oop.hxx"
#include "ltnvm/Value.hxx"

namespace ltn::vm {
	struct VMCore;
	class Type : stx::non_copyable, stx::non_moveable {
	public:
		virtual bool is(const Value &, VMCore &) const = 0;
		virtual Value cast(const Value &, VMCore &) const = 0;
		virtual std::string name(VMCore &) const = 0;
	};


	std::string type_name(const Type & type, VMCore & core);
	bool type_is(const Type & type, const Value & value, VMCore & core);
	Value type_cast(const Type & type, const Value & value, VMCore & core);
}