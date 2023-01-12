#pragma once
#include <vector>
#include "stdxx/float64_t.hxx"
#include "ltnvm/memory/Value.hxx"
#include "ltnvm/memory/Heap.hxx"
#include "ltnvm/type_check.hxx"

namespace ltn::vm::ext {
	class Parameters {
	public:
		Parameters(Heap & heap, const Array & params);

		template<class T>
		T get(std::size_t idx) const {
			const Value & value = this->get_value(idx);

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
				if(is_string(value)) return this->heap.read<String>(value.u);
				throw std::runtime_error{"Parameter not a string"};
			}
			else {
				throw std::runtime_error{"Unknown parameter type in external"};
			}
		}

		virtual ~Parameters();

	private:
		const Value & get_value(std::size_t idx) const {
			if(idx >= params.size()) {
				throw std::runtime_error{"Parameter out of range"};
			}
			return this->params[idx];
		}
		Heap & heap;
		Array params;
	};
}