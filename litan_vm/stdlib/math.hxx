#pragma once
#include "litan_vm/VMCore.hxx"

namespace ltn::vm::stdlib {
	struct min {
		constexpr static inline std::uint64_t arity = 2; 
		static Value func(Context * context, const Value * args);
	};



	struct max {
		constexpr static inline std::uint64_t arity = 2; 
		static Value func(Context * context, const Value * args);
	};



	struct clamp {
		constexpr static inline std::uint64_t arity = 3; 
		static Value func(Context * context, const Value * args);/*  */
	};



	struct round {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context * context, const Value * args);
	};



	struct floor {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context * context, const Value * args);
	};



	struct ceil {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context * context, const Value * args);
	};



	struct abs {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context * context, const Value * args);
	};



	struct sin {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context * context, const Value * args);
	};



	struct cos {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context * context, const Value * args);
	};



	struct tan {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context * context, const Value * args);
	};



	struct sqrt {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context * context, const Value * args);
	};



	struct hypot {
		constexpr static inline std::uint64_t arity = 2; 
		static Value func(Context * context, const Value * args);
	};



	struct log {
		constexpr static inline std::uint64_t arity = 2; 
		static Value func(Context * context, const Value * args);
	};



	struct ln {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context * context, const Value * args);
	};



	struct ld {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context * context, const Value * args);
	};



	struct lg {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context * context, const Value * args);
	};
}