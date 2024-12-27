#pragma once
#include "litan_vm/Value.hxx"
#include "litan_vm/native/native.hxx"


namespace ltn::vm::stdlib {
	struct ord {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct chr {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct str {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct call_stack_depth {
		constexpr static inline std::uint64_t arity = 0;
		static Value func(Context *, const Value * args);
	};
}