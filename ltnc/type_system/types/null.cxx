#include "null.hxx"
#include "../types.hxx"

namespace ltn::c::type {
	bool Null::is_assignable_from(const Type & type) {
		return type.is<Null>();
	}
}