#include "boolean.hxx"
#include "../types.hxx"

namespace ltn::c::type {
	bool Boolean::is_assignable_from(const Type & type) {
		return type.is<Boolean>();
	}
}