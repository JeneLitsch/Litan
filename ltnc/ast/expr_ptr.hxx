#pragma once
#include <memory>

namespace ltn::c::ast {
	struct Expression;

	struct expr_ptr {
		template<typename T>
		expr_ptr(std::unique_ptr<T> ptr)
			: ptr {std::move(ptr)} {}

		template<typename T>
		expr_ptr(T && node)
			: ptr {std::make_unique<Expression>(std::move(node))} {}

		expr_ptr() : ptr {nullptr} {}
		
		operator bool() const {
			return static_cast<bool>(ptr);
		}
		
		const Expression & operator* () const {
			return *ptr;
		}
		
		Expression & operator* () {
			return *ptr;
		}

		const Expression * operator-> () const {
			return ptr.get();
		}
		
		Expression * operator-> () {
			return ptr.get();
		}
		
		std::unique_ptr<Expression> ptr;
	};
}