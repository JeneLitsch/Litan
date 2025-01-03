#pragma once
#include "litan_vm/Value.hxx"
#include "litan_vm/native/native.hxx"

namespace ltn::vm::stdlib {
	struct tuple_new {
		constexpr static inline std::uint64_t arity = 0;
		static Value func(Context *, const Value * args);
	};

	struct tuple_is {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct tuple_cast {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct tuple_size {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct tuple_is_empty {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct tuple_at {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context *, const Value * args);
	};

	struct tuple_front {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct tuple_back {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct tuple_values {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};
}