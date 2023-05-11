#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include "stdxx/oop.hxx"
#include "ltnvm/memory/Value.hxx"

namespace ltn::vm {
	class Heap;
	class TypeNode : stx::non_copyable, stx::non_moveable {
	public:
		virtual bool is(const Value & value, Heap & heap) const = 0;
		virtual Value cast(const Value & value, Heap & heap) const = 0;
		virtual std::string name() const = 0;
	};

	struct Type {
		const TypeNode * node;
	};

	inline Type clone(const Type & type) {
		return type;
	}


	std::string type_name(const Type & type);
	bool type_is(const Type & type, const Value & value, Heap & heap);
	Value type_cast(const Type & type, const Value & value, Heap & heap);
}