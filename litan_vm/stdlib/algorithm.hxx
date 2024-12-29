#pragma once
#include "litan_vm/Value.hxx"
#include "litan_vm/native/native.hxx"

namespace ltn::vm::stdlib {
	
	// Algorithm
	struct sort_desc {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(ltn_Context * context, const Value * args);
	};

	struct sort_ascn {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(ltn_Context * context, const Value * args);
	};

	struct is_sorted_ascn {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(ltn_Context * context, const Value * args);
	};

	struct is_sorted_desc {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(ltn_Context * context, const Value * args);
	};

	struct find {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(ltn_Context * context, const Value * args);
	};

	struct fill {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(ltn_Context * context, const Value * args);
	};

	struct reverse {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(ltn_Context * context, const Value * args);
	};

	struct reduce_l_2 {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(ltn_Context * context, const Value * args);
	};

	struct reduce_l_3 {
		constexpr static inline std::uint64_t arity = 3;
		static Value func(ltn_Context * context, const Value * args);
	};

}