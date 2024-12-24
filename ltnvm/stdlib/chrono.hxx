#pragma once
#include "ltnvm/VMCore.hxx"

namespace ltn::vm::stdlib {
	struct clock {
		constexpr static inline std::uint64_t arity = 0; 
		static Value func(Context *, const Value * args);
	};


	struct to_seconds {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context *, const Value * args);
	};



	struct to_milliseconds {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context *, const Value * args);
	};
}