#pragma once
#include <memory>
#include <functional>
#include "litan_vm/Value.hxx"
#include "litan_vm/Heap.hxx"
#include "litan_vm/external/Parameters.hxx"
#include "litan_vm/external/wrap_return.hxx"

namespace ltn::vm::ext {
	template<std::size_t ... INDICES, typename ... Args>
	static auto wrap_function(std::function<void(Args...)> fx, std::index_sequence<INDICES...>) {
		return [fx = std::move(fx)] (Parameters & parameters, Heap &) -> Value {
			fx((parameters.get<Args>(INDICES))...);
			return value::null;
		};
	}



	template<std::size_t ... INDICES, typename R, typename ... Args>
	static auto wrap_function(std::function<R(Args...)> fx, std::index_sequence<INDICES...>) {
		return [fx = std::move(fx)] (Parameters & parameters, Heap & heap) -> Value {
			R result = fx((parameters.get<Args>(INDICES))...);
			return wrap_return(std::move(result), heap);
		};
	}
	


	class Callable final {
	public:

		Callable(auto fx) : Callable {std::function{std::move(fx)}} {}

		template<typename R, typename ... Args>
		Callable(std::function<R(Args...)> fx)
			: callable    { wrap_function(std::move(fx), std::make_index_sequence<sizeof...(Args)>()) }
			, arity_value { sizeof...(Args) } {}

		Callable(const Callable &) = default;
		Callable & operator=(const Callable &) = default;
		Callable(Callable &&) = default;
		Callable & operator=(Callable &&) = default;
		
		~Callable() = default;



		Value operator()(ext::Parameters & parameters, Heap & heap) {
			return this->callable(parameters, heap);
		}



		std::size_t arity() const {
			return this->arity_value;
		}
 


	private:

		std::function<Value(Parameters & parameters, Heap & heap)> callable;
		std::size_t arity_value = 0;
	};
}