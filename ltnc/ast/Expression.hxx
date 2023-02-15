#pragma once
#include <memory>

namespace ltn::c::ast {
	struct ExprBase;

	class Expression {
	public:
		template<typename T>
		Expression(std::unique_ptr<T> ptr)
			: ptr {std::move(ptr)} {}

		template<typename T>
		Expression(T && node)
			: ptr {std::make_unique<ExprBase>(std::move(node))} {}

		Expression() : ptr {nullptr} {}
		
		operator bool() const {
			return static_cast<bool>(ptr);
		}
		
		const ExprBase & operator* () const {
			return *ptr;
		}
		
		ExprBase & operator* () {
			return *ptr;
		}

		const ExprBase * operator-> () const {
			return ptr.get();
		}
		
		ExprBase * operator-> () {
			return ptr.get();
		}


		template<class To>
		const To * as() const {
			return dynamic_cast<const To*>(ptr.get());
		}

	private:
		std::unique_ptr<ExprBase> ptr;
	};
}