#pragma once
#include "Type.hxx"

namespace ltn::c::type {
	Array deduce_array_append(const Array & array, const Type & elem);

	Type deduce_add(const Type & l, const Type & r);
	Type deduce_sub(const Type & l, const Type & r);
	Type deduce_mlt(const Type & l, const Type & r);
	Type deduce_div(const Type & l, const Type & r);
	Type deduce_mod(const Type & l, const Type & r);
	Type deduce_pow(const Type & l, const Type & r);

	Type deduce_bitwise(const Type & l, const Type & r);

	Type deduce_compare(const Type & l, const Type & r);
	Type deduce_three_way(const Type & l, const Type & r);
	Type deduce_index(const Type & container, const Type & key, std::optional<std::uint64_t> index = std::nullopt);

	Type deduce_logic(const Type & l, const Type & r);

	Type deduce_elvis(const Type & l, const Type & r);
	Type deduce_nullco(const Type & l, const Type & r);

	Type deduce_ternary(const Type & condition, const Type & l, const Type & r);

	Type deduce_choose(const Type & current, const Type & next);

	Type deduce_neg(const Type & x);
	Type deduce_not(const Type & x);
	Type deduce_bitnot(const Type & x);
	Type deduce_nulltest(const Type & x);
	Type deduce_deref(const Type & x);

	Type deduce_invokation(const Type & fx_ptr);

	Type deduce_cast_static(const Type & cast_to);
	Type deduce_cast_dynamic(const Type & cast_to);
	Type deduce_copy_static(const Type & cast_to);
	Type deduce_copy_dynamic(const Type & cast_to);
}