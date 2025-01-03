#pragma once
#include "litan_vm/Value.hxx"
#include "litan_vm/native/native.hxx"

namespace ltn::vm::stdlib {
	struct struct_new {
		constexpr static inline std::uint64_t arity = 0;
		static Value func(Context * context, const Value * args);
	};

	struct struct_is {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};

	struct struct_cast {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};
}