#pragma once
#include "litan_vm/Value.hxx"
#include "litan_vm/native/native.hxx"

namespace ltn::vm::stdlib {
	struct array_new {
		constexpr static inline std::uint64_t arity = 0; 
		static Value func(Context *, const Value * args);
	};

	struct array_is {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context *, const Value * args);
	};

	struct array_cast {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context *, const Value * args);
	};

	struct array_size {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context *, const Value * args);
	};

	struct array_is_empty {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};
	
	struct array_push {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context *, const Value * args);
	};

	struct array_pop {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct array_front {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct array_back {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct array_peek {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * native_api, const Value * args);
	};

	struct array_at {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context *, const Value * args);
	};

	struct array_insert {
		constexpr static inline std::uint64_t arity = 3;
		static Value func(Context *, const Value * args);
	};

	struct array_erase {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context *, const Value * args);
	};

	struct array_values {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct array_filter {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context * context, const Value * args);
	};

	struct array_transform {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context * context, const Value * args);
	};

	struct array_reduce {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context * context, const Value * args);
	};

	struct array_any {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context * context, const Value * args);
	};

	struct array_all {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context * context, const Value * args);
	};

	struct array_has {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context * context, const Value * args);
	};

	struct array_none {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context * context, const Value * args);
	};

	struct array_slice {
		constexpr static inline std::uint64_t arity = 3;
		static Value func(Context * context, const Value * args);
	};

	struct array_prefix {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context * context, const Value * args);
	};

	struct array_suffix {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context * context, const Value * args);
	};

	struct array_reversed {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};

	struct array_zipped {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context * context, const Value * args);
	};
}