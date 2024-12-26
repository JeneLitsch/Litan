#pragma once
#include "litan_vm/Value.hxx"
#include "litan_vm/native/native.hxx"

namespace ltn::vm::stdlib {
	struct json_print {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context *, const Value * args);
	};

	struct json_parse {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};
} 