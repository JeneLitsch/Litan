#pragma once
#include "ltnvm/Value.hxx"
#include "ltnvm/native/native.hxx"


namespace ltn::vm::stdlib {
	struct ord {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};

	struct chr {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};
}