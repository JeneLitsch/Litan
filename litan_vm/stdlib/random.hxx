#pragma once
#include "litan_vm/Value.hxx"
#include "litan_vm/native/native.hxx"

namespace ltn::vm::stdlib {
	struct mersenne_0 {
		constexpr static inline std::uint64_t arity = 0;
		static Value func(ltn_Context * context, const Value * args);
	};

	struct mersenne_1 {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(ltn_Context * context, const Value * args);
	};

	struct split {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(ltn_Context * context, const Value * args);
	};

	struct rand {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(ltn_Context * context, const Value * args);
	};

	struct rand_int {
		constexpr static inline std::uint64_t arity = 3;
		static Value func(ltn_Context * context, const Value * args);
	};

	struct rand_float {
		constexpr static inline std::uint64_t arity = 3;
		static Value func(ltn_Context * context, const Value * args);
	};

}