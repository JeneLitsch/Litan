#pragma once

#include "litan_vm/Value.hxx"
#include "litan_vm/native/native.hxx"

namespace ltn::vm::stdlib {
	struct cout {
		constexpr static inline std::uint64_t arity = 0; 
		static Value func(Context * context, const Value * args);
	};



	struct fout {
		constexpr static inline std::uint64_t arity = 2; 
		static Value func(Context * context, const Value * args);
	};



	struct strout {
		constexpr static inline std::uint64_t arity = 0; 
		static Value func(Context * context, const Value * args);
	};



	struct cin {
		constexpr static inline std::uint64_t arity = 0; 
		static Value func(Context * context, const Value * args);
	};



	struct fin {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context * context, const Value * args);
	};



	struct strin {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context * context, const Value * args);
	};



	struct close_stream {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context * context, const Value * args);
	};



	struct is_eof {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context * context, const Value * args);
	};



	struct print {
		constexpr static inline std::uint64_t arity = 2; 
		static Value func(Context * context, const Value * args);
	};



	struct read_str {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context * context, const Value * args);
	};



	struct read_line {
		constexpr static inline std::uint64_t arity = 1; 
		static Value func(Context * context, const Value * args);
	};



	struct read_bool {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};



	struct read_char {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};



	struct read_int {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};



	struct read_float {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};



	struct read_all {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};



	struct set_fg_color {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context * context, const Value * args);
	};



	struct set_bg_color {
		constexpr static inline std::uint64_t arity = 2;
		static Value func(Context * context, const Value * args);
	};



	struct reset_color {
		constexpr static inline std::uint64_t arity = 1;
		static Value func(Context * context, const Value * args);
	};
}