#pragma once

namespace ltn::c::type {
	class Type;
	struct Array;

	Array deduce_array_append(const Array & array, const Type & elem);

	Type deduce_add(const Type & l, const Type & r);
	Type deduce_sub(const Type & l, const Type & r);
	Type deduce_mlt(const Type & l, const Type & r);
	Type deduce_div(const Type & l, const Type & r);
	Type deduce_mod(const Type & l, const Type & r);
	Type deduce_pow(const Type & l, const Type & r);

	Type deduce_neg(const Type & x);
	Type deduce_not(const Type & x);

	Type deduce_index(const Type & container, const Type & key);
}