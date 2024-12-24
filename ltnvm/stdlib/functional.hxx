#pragma once
#include "ltnvm/Value.hxx"
#include "ltnvm/native/native.hxx"

namespace ltn::vm::stdlib {
	struct function_arity {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);	
	};


	struct function_call {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context * context, const Value * args);	
	};


	struct function_is_variadic {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);	
	};
}