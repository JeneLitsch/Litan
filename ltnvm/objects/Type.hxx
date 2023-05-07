#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include "ltnvm/memory/Value.hxx"
#include "ltnvm/objects/type/type_name.hxx"
#include "ltnvm/objects/type/type_cast.hxx"
#include "ltnvm/objects/type/type_is.hxx"

namespace ltn::vm {
	class Heap;

	struct Type {
		std::vector<std::uint8_t> code;
	};

	inline Type clone(const Type & type) {
		return type;
	}
}