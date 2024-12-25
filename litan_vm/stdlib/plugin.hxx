#pragma once
#include "litan_vm/VMCore.hxx"

namespace ltn::vm::stdlib {
	struct load_plugin {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context *, const Value * args);
	};
}