#include "floating.hxx"
#include "../types.hxx"

namespace ltn::c::type {
	bool Floating::is_assignable_from(const Type & type) {
		return type.is<Floating>();
	}
}