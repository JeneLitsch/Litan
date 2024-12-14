#pragma once
#include "ltnvm/Value.hxx"
#include "ltnvm/native/native.hxx"

namespace ltn::vm::stdlib {
	struct tuple_size{
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct tuple_is_empty{
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct tuple_at{
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context *, const Value * args);
	};

	struct tuple_front{
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct tuple_back{
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};
}