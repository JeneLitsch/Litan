#pragma once
#include <memory>
#include <functional>
#include "ltnvm/memory/Value.hxx"
#include "ltnvm/memory/Heap.hxx"
#include "ltnvm/external/Parameters.hxx"
#include "ltnvm/external/wrap_return.hxx"

namespace ltn::vm::ext {
	class Callable final {

		struct CallableConcept {
			virtual Value call(Parameters & parameters, Heap & heap) const = 0;
			virtual std::size_t get_arity() const = 0;
			virtual std::unique_ptr<CallableConcept> clone() const = 0;
			virtual ~CallableConcept() = default;
		};



		template<typename R, typename ... Args>
		struct CallableModel : CallableConcept {
			CallableModel(std::function<R(Args...)> fx)
				: fx {std::move(fx)} {}
			
			virtual Value call(Parameters & parameters, Heap & heap) const override {
				
				return do_call(parameters, heap, INDICES);
			}

			template<std::size_t ... INDICES>
			Value do_call(
				Parameters & parameters,
				Heap & heap,
				std::index_sequence<INDICES...>) const {
				
				if constexpr (std::same_as<R, void>) {
					fx((parameters.get<Args>(INDICES))...);
					return value::null;
				}
				else {
					R result = fx((parameters.get<Args>(INDICES))...);
					return wrap_return(result, heap);
				}
			}

			virtual std::size_t get_arity() const override {
				return sizeof...(Args);
			}

			virtual std::unique_ptr<CallableConcept> clone() const override { 
				return std::make_unique<CallableModel<R, Args...>>(*this);
			}

			std::function<R(Args...)> fx;
			static constexpr auto ARITY = sizeof...(Args);
			static constexpr auto INDICES = std::make_index_sequence<ARITY>();
		};



	public:

		Callable(auto fx) : Callable{std::function{fx}} {}

		Callable(const Callable & other) {
			this->callable_object = other.callable_object->clone();
		}

		Callable & operator=(const Callable & other) {
			this->callable_object = other.callable_object->clone();
			return *this;
		}

		Callable(Callable &&) = default;

		Callable & operator=(Callable &&) = default;
		
		~Callable() = default;

		Value operator()(ext::Parameters & parameters, Heap & heap) {
			return this->callable_object->call(parameters, heap);
		}

		std::size_t arity() const {
			return this->callable_object->get_arity();
		}
 


	private:

		template<typename R, typename ... Args>
		Callable(std::function<R(Args...)> fx)
			: callable_object { std::make_unique<CallableModel<R, Args...>>(fx) } {}

		Callable(std::unique_ptr<CallableConcept> callable_object)
			: callable_object { std::move(callable_object) } {}

		std::unique_ptr<CallableConcept> callable_object;
	};
}