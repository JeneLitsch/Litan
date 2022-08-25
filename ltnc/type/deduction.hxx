#pragma once

namespace ltn::c::type {
	class Type;
	struct Array;

	Array deduce_array_append(const Array & array, const Type & elem);

	Type deduce_add(const Type & l, const Type & r);
	Type deduce_sub(const Type & l, const Type & r);
}