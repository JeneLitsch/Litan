#pragma once
#include <memory>
#include <functional>
#include "ltnvm/memory/Value.hxx"
#include "ltnvm/memory/Register.hxx"
#include "ltnvm/memory/Heap.hxx"
#include "ltnvm/external/Api.hxx"

namespace ltn::vm {
	class Callable final {
		struct CallableConcept {
			virtual void call(ext::Api & api) const = 0;
			virtual std::size_t get_arity() const = 0;
			virtual std::unique_ptr<CallableConcept> clone() const = 0;
			virtual ~CallableConcept() = default;
		};

		template<typename R, typename ... Args>
		struct CallableModel : CallableConcept {
			CallableModel(std::function<R(Args...)> fx)
				: fx {std::move(fx)} {}
			
			virtual void call(ext::Api & api) const override {
				static constexpr auto ARITY = sizeof...(Args);
				do_call(api, std::make_index_sequence<ARITY>());
			}


			template<std::size_t ... INDICES>
			void do_call(ext::Api & api, std::index_sequence<INDICES...>) const {
				if constexpr (std::same_as<R, void>) {
					fx((api.parameter<Args>(INDICES))...);
				}
				else {
					R result = fx((api.parameter<Args>(INDICES))...);
					api.return_value(result);
				}
			}


			virtual std::size_t get_arity() const override {
				return sizeof...(Args);
			}


			virtual std::unique_ptr<CallableConcept> clone() const override { 
				return std::make_unique<CallableModel<R, Args...>>(*this);
			}


			std::function<R(Args...)> fx;
		};

	public:
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

		static Callable modern(auto fx) {
			return Callable{std::function{fx}};
		}

		void operator()(ext::Api & api) {
			this->callable_object->call(api);
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