#include "ltnc/type/deduction.hxx"
#include "ltnc/type/Type.hxx"

namespace ltn::c::type {
	Array deduce_array_append(const Array & array, const Type & elem) {
		if(!array.contains) return Array{elem};
		if(**array.contains == elem) return array;
		return Array{Any{}};
	}
}