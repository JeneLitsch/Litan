#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include "stdxx/oop.hxx"
#include "ltnvm/Value.hxx"

namespace ltn::vm {
	struct VmCore;
	class TypeNode : stx::non_copyable, stx::non_moveable {
	public:
		virtual bool is(const Value &, VmCore &) const = 0;
		virtual Value cast(const Value &, VmCore &) const = 0;
		virtual std::string name() const = 0;
	};

	struct Type {
		const TypeNode * node;
	};

	inline Type clone(const Type & type) {
		return type;
	}


	std::string type_name(const TypeNode & type);
	bool type_is(const TypeNode & type, const Value & value, VmCore & core);
	Value type_cast(const TypeNode & type, const Value & value, VmCore & core);
}