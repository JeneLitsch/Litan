#pragma once
#include "litan_vm/Value.hxx"
#include "litan_vm/native/native.hxx"


namespace ltn::vm::stdlib {
	struct iter_range {
		constexpr static inline std::uint64_t arity = 3;
		static Value func(Context * context, const Value * args);
	};

	struct iter_next {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};

	struct iter_get {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};

	struct iter_move {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context * context, const Value * args);
	};

	struct iter_iter {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};

	struct iter_combined {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};

	struct iter_is_stop {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};

	struct iter_reversed {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};

}