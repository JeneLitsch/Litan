#pragma once
#include "litan_vm/Value.hxx"
#include "litan_vm/native/native.hxx"

namespace ltn::vm::stdlib {
	struct map_new {
		constexpr static inline std::uint64_t arity = 0;
		static Value func(Context *, const Value * args);
	};

	struct map_size {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct map_is_empty {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct map_at {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context *, const Value * args);
	};

	struct map_has {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context *, const Value * args);
	};

	struct map_insert {
		constexpr static inline std::uint64_t arity = 3;
		static Value func(Context *, const Value * args);
	};

	struct map_erase {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context * context, const Value * args);
	};

	struct map_keys {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};

	struct map_values {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};

	struct map_merged {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context * context, const Value * args);
	};

}