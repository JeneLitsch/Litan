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
		inline T convert(const Value & value);



		template<typename ...T, std::size_t... I>
		inline std::tuple<T...> make_tuple_from_vector_impl(const std::vector<Value> & values, std::index_sequence<I...>) {
			return std::make_tuple(
				(convert<T>(values[I]))...
			);
		}



		template<typename ...T>
		inline std::tuple<T...> make_tuple_from_vector(const std::vector<Value> & values, const std::tuple<T...> &) {
			return make_tuple_from_vector_impl<T...>(values, std::make_index_sequence<sizeof...(T)>{});
		}



		inline bool convert_to_bool(const Value & value) {
			if(is_bool(value)) return value.b;
			throw std::runtime_error{"Parameter not a boolean"};
		}




		template<std::integral T>
		inline T convert_to_int(const Value & value) {
			if(is_int(value)) return value.i;
			throw std::runtime_error{"Parameter not an integer"};
		}



		template<std::floating_point T>
		inline T convert_to_float(const Value & value) {
			if(is_float(value)) return value.f;
			throw std::runtime_error{"Parameter not a float"};
		}



		inline std::string convert_to_string(const Value & value) {
			if(is_string(value)) return value.as<String>()->data;
			throw std::runtime_error{"Parameter not a string"};
		}



		template<typename T>
		inline T convert_to_array(const Value & value) {
			if(is_array(value)) {
				auto & input = *value.as<Array>();
				T output;
				for(const auto & elem : input.data) {
					output.push_back(convert<typename T::value_type>(elem));
				}
				return output;
			} 
			else {
				throw std::runtime_error{"Parameter not an array"};
			}
		}



		template<typename T>
		inline T convert_to_tuple(const Value & value) {
			if(is_tuple(value)) {
				auto & input = *value.as<Array>();
				return make_tuple_from_vector(input.data, T{});
			} 
			else {
				throw std::runtime_error{"Parameter not an array"};
			}
		}



		template<class T>
		inline T convert(const Value & value) {
			if      constexpr(std::same_as<T, bool>)            return convert_to_bool(value);
			else if constexpr(std::is_integral<T>::value)       return convert_to_int<T>(value);
			else if constexpr(std::is_floating_point<T>::value) return convert_to_float<T>(value);
			else if constexpr(is_tuple_type<T>::value)          return convert_to_tuple<T>(value);
			else if constexpr(std::same_as<T, std::string>)     return convert_to_string(value);
			else if constexpr(is_vector_type<T>::value)         return convert_to_array<T>(value);
			else throw std::runtime_error{"Unknown parameter type in external"};
		}
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
			return impl::convert<T>(value);
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