#pragma once
#include <vector>
#include "stdxx/float64_t.hxx"
#include "ltnvm/Value.hxx"
#include "ltnvm/Heap.hxx"
#include "ltnvm/utils/type_check.hxx"

namespace ltn::vm::ext {

	template <typename> struct is_tuple_type: std::false_type {};
	template <typename ...T> struct is_tuple_type<std::tuple<T...>>: std::true_type {};

	template <typename> struct is_vector_type: std::false_type {};
	template <typename T> struct is_vector_type<std::vector<T>>: std::true_type {};


	namespace impl {
		template<class T>
		struct Converter {
			static T convert(const Value & value) {
				throw std::runtime_error{"Unknown parameter type in external"};
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
				if(is_int(value)) return value.i;
				throw std::runtime_error{"Parameter not an integer"};
			}
		};


		
		template<std::floating_point T>
		struct Converter<T> {
			static T convert(const Value & value) {
				if(is_float(value)) return value.f;
				throw std::runtime_error{"Parameter not a float"};
			}
		};


		
		template<>
		struct Converter<std::string> {
			static std::string convert(const Value & value) {
				if(is_string(value)) return value.as<String>()->data;
				throw std::runtime_error{"Parameter not a string"};
			}
		};



		template<typename ...T, std::size_t... I>
		inline std::tuple<T...> make_tuple_from_vector_impl(const std::vector<Value> & values, std::index_sequence<I...>) {
			return std::make_tuple(
				(Converter<T>::convert(values[I]))...
			);
		}



		template<typename ...T>
		inline std::tuple<T...> make_tuple_from_vector(const std::vector<Value> & values, const std::tuple<T...> &) {
			return make_tuple_from_vector_impl<T...>(values, std::make_index_sequence<sizeof...(T)>{});
		}



		template<typename T>
		struct Converter<std::vector<T>> {
			static std::vector<T> convert(const Value & value) {
				if(is_array(value)) {
					auto & input = *value.as<Array>();
					std::vector<T> output;
					for(const auto & elem : input.data) {
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
			static std::tuple<T...> convert(const Value & value) {
				if(is_tuple(value)) {
					auto & input = *value.as<Array>();
					return make_tuple_from_vector(input.data, std::tuple<T...>{});
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
		Heap & heap;
		std::vector<Value> params;
	};
}