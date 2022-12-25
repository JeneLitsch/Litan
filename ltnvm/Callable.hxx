#pragma once
#include <memory>
#include <functional>
#include "memory/Value.hxx"
#include "memory/Register.hxx"
#include "memory/Heap.hxx"
#include "external/Api.hxx"
#include "external/External.hxx"

namespace ltn::vm {
	class Callable {
		struct CallableConcept {
			virtual void call(ext::Api & api) const = 0;
			virtual std::size_t get_arity() const = 0;
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

			std::function<R(Args...)> fx;
		};


		struct CallableModelLegacy : CallableConcept {
			CallableModelLegacy(std::unique_ptr<ext::External> fx)
				: fx {std::move(fx)} {}
			
			virtual void call(ext::Api & api) const override {
				(*fx)(api);
			}

			virtual std::size_t get_arity() const override {
				return fx->get_parameters();
			}

			std::unique_ptr<ext::External> fx;
		};
	public:
		static Callable legacy(std::unique_ptr<ext::External> fx) {
			return Callable{std::make_unique<CallableModelLegacy>(
				std::move(fx)
			)};
		}


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