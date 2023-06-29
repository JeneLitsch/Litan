#pragma once
#include <vector>
#include "stdxx/float64_t.hxx"
#include "ltnvm/Value.hxx"
#include "ltnvm/Heap.hxx"
#include "ltnvm/utils/type_check.hxx"

namespace ltn::vm::ext {
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
			return convert<T>(value);
		}



		template<class T>
		T convert(const Value & value) const {
			if constexpr(std::same_as<T, bool>) {
				if(is_bool(value)) return value.b;
				throw std::runtime_error{"Parameter not a boolean"};
			}
			else if constexpr(std::integral<T>) {
				if(is_int(value)) return value.i;
				throw std::runtime_error{"Parameter not an integer"};
			}
			else if constexpr(std::floating_point<T>) {
				if(is_float(value)) return value.f;
				throw std::runtime_error{"Parameter not a float"};
			}
			else if constexpr(std::same_as<T, std::string>) {
				if(is_string(value)) return this->heap.read<String>(value);
				throw std::runtime_error{"Parameter not a string"};
			}
			else if constexpr(std::same_as<T, std::vector<typename T::value_type>>) {
				if(is_array(value)) {
					auto & input = this->heap.read<Array>(value);
					T output;
					for(const auto & elem : input.data) {
						output.push_back(convert<typename T::value_type>(elem));
					}
					return output;
				} 
				else {
					throw std::runtime_error{"Parameter not a string"};
				}
			}
			else {
				throw std::runtime_error{"Unknown parameter type in external"};
			}
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