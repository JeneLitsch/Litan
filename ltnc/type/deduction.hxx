#pragma once

namespace ltn::c::type {
	class Type;
	struct Array;

	Array deduce_array_append(const Array & array, const Type & elem);
}