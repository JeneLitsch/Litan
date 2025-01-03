#pragma once
#include <vector>
#include "stdxx/float64_t.hxx"
#include "litan_vm/Value.hxx"
#include "litan_vm/Heap.hxx"
#include "litan_vm/utils/type_check.hxx"
#include "litan_vm/utils/to_any.hxx"

namespace ltn::vm::ext {
	namespace impl {
		template<class T>
		struct Converter {
			static T convert(const Value &) {
				throw std::runtime_error{"Unknown parameter type in external"};
			}
		};




		template<>
		struct Converter<Any> {
			static Any convert(const Value & value) {
				return to_any(value);
			}
		};



		template<>
		struct Converter<bool> {
			static bool convert(const Value & value) {
				if(is_bool(value)) return value.b;
				throw std::runtime_error{"Parameter not a boolean"};
			}
		};


		
		template<std::integral T>
		struct Converter<T> {
			static T convert(const Value & value) {
				if(is_int(value)) return static_cast<T>(value.i);
				throw std::runtime_error{"Parameter not an integer"};
			}
		};


		
		template<std::floating_point T>
		struct Converter<T> {
			static T convert(const Value & value) {
				if(is_float(value)) return static_cast<T>(value.f);
				throw std::runtime_error{"Parameter not a float"};
			}
		};


		
		template<>
		struct Converter<std::string> {
			static std::string convert(const Value & value) {
				if(is_string(value)) return value::as<String>(value)->copy_to_std_string();
				throw std::runtime_error{"Parameter not a string"};
			}
		};



		template<typename T>
		struct Converter<std::vector<T>> {
			static std::vector<T> convert(const Value & value) {
				if(is_contiguous(value)) {
					auto & input = *value::as<Contiguous>(value);
					std::vector<T> output;
					for(const auto & elem : input) {
						output.push_back(Converter<T>::convert(elem));
					}
					return output;
				} 
				else {
					throw std::runtime_error{"Parameter not an array"};
				}
			}
		};



		template<typename ... T>
		struct Converter<std::tuple<T...>> {
						
			template<std::size_t... I>
			static std::tuple<T...> make_tuple_from_vector(const std::vector<Value> & values, std::index_sequence<I...>) {
				return std::make_tuple(
					(Converter<T>::convert(values[I]))...
				);
			}

			static std::tuple<T...> convert(const Value & value) {
				if(is_tuple(value)) {
					auto & input = *value::as<Tuple>(value);
					return make_tuple_from_vector(input.get_underlying(), std::make_index_sequence<sizeof...(T)>{});
				} 
				else {
					throw std::runtime_error{"Parameter not an array"};
				}
			}
		};
	}



	class Parameters {
	public:
		Parameters(Heap & heap, const std::vector<Value> & params);

		template<class T>
		T get(std::size_t idx) const {
			return this->get<T>(idx, this->params);
		}

		virtual ~Parameters();

	private:
		template<class T>
		T get(std::size_t idx, const std::vector<Value> & array) const {
			const Value & value = get_value(idx, array);
			return impl::Converter<T>::convert(value);
		}



		const Value & get_value(std::size_t idx, const std::vector<Value> & array) const {
			if(idx >= std::size(array)) {
				throw std::runtime_error{"Parameter out of range"};
			}
			return array[idx];
		}
		std::vector<Value> params;
	};
}