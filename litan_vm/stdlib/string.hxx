#pragma once
#include "litan_vm/Value.hxx"
#include "litan_vm/native/native.hxx"

namespace ltn::vm::stdlib {
	struct string_new {
		constexpr static inline std::uint64_t arity = 0;
		static Value func(Context * context, const Value * args);
	};

	struct string_is {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};

	struct string_cast {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};

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