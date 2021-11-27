#pragma once
#include <vector>
#include "ltnvm/memory/Value.hxx"
#include "ltnvm/memory/Heap.hxx"
#include "ltnvm/TypeCheck.hxx"

namespace ltn::vm::ext {
	class Api {
	public:
		Api(Heap & heap, const std::vector<Value> & params);

		template<class T>
		T parameter(std::size_t idx) const {
			if(idx >= params.size()) {
				throw std::runtime_error{"Parameter out of range"};
			}
			const Value & value = this->params[idx];

			if constexpr(std::same_as<T, bool>) {
				if(isBool(value)) return value.b;
				throw std::runtime_error{"Parameter not a boolean"};
			}
			else if constexpr(std::integral<T>) {
				if(isInt(value)) return value.i;
				throw std::runtime_error{"Parameter not an integer"};
			}
			else if constexpr(std::floating_point<T>) {
				if(isFloat(value)) return value.f;
				throw std::runtime_error{"Parameter not a float"};
			}
			else if constexpr(std::same_as<T, std::string>) {
				if(isStr(value)) return this->heap.readString(value.u);
				throw std::runtime_error{"Parameter not a string"};
			}
			else {
				throw std::runtime_error{"Unknown parameter type in external"};
			}
		}

	private:
		Heap & heap;
		std::vector<Value> params;
	};
}