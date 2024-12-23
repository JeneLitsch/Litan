#include "integer.hxx"
#include "../types.hxx"

namespace ltn::c::type {
	bool Integer::is_assignable_from(const Type & type) {
		return type.is<Integer>();
	}
}