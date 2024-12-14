#pragma once
#include "ltnvm/Value.hxx"
#include "ltnvm/native/native.hxx"

namespace ltn::vm::stdlib {
	struct stack_size {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct stack_is_empty {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct stack_push {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context *, const Value * args);
	};

	struct stack_pop {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct stack_values {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};
}
