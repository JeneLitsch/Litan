#pragma once
#include "litan_vm/Value.hxx"
#include "litan_vm/native/native.hxx"

namespace ltn::vm::stdlib {
	struct queue_new {
		constexpr static inline std::uint64_t arity = 0;
		static Value func(Context *, const Value * args);
	};

	struct queue_is {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct queue_cast {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct queue_size {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct queue_is_empty {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct queue_push {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context *, const Value * args);
	};

	struct queue_pop {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct queue_values {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};
}