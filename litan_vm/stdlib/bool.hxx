#pragma once
#include "litan_vm/Value.hxx"
#include "litan_vm/native/native.hxx"


namespace ltn::vm::stdlib {
	struct boolean_new {
		constexpr static inline std::uint64_t arity = 0;
		static Value func(ltn_Context * context, const Value * args);
	};

	struct boolean_is {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(ltn_Context * context, const Value * args);
	};

	struct boolean_cast {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(ltn_Context * context, const Value * args);
	};
}