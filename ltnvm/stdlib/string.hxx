#pragma once
#include "ltnvm/Value.hxx"
#include "ltnvm/native/native.hxx"

namespace ltn::vm::stdlib {
	struct string_size {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};

	struct string_is_empty {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};

	struct string_split {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context * context, const Value * args);
	};
}