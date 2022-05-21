#include "LtnVM.hxx"
#include <cmath>
#include "type_check.hxx"
#include <sstream>
#include "Operations.hxx"
#include "calcBinary.hxx"
#include "convert.hxx"

#define FETCH\
	const auto r = this->core.reg.pop();\
	const auto l = this->core.reg.pop();

namespace ltn::vm {
	namespace {
		template<class T>
		std::vector<T> operator+(
			const std::vector<T> & l,
			const std::vector<T> & r) {
			std::vector<T> vec;
			vec.reserve(l.size() + r.size());
			vec.insert(std::end(vec), l.begin(), l.end());
			vec.insert(std::end(vec), r.begin(), r.end());
			return vec;
		}


		Array toArray(const Value & value, Heap & heap) {
			if(is_array(value)) {
				return heap.read<Array>(value.u);
			}
			return {{value}};
		}
	}


	void LtnVM::add() {
		FETCH
		
		if(is_array(l) && is_array(r)) {
			const auto arr_l = toArray(l, this->core.heap).get();
			const auto arr_r = toArray(r, this->core.heap).get();
			const auto ref = this->core.heap.alloc<Array>({arr_l + arr_r});
			return this->core.reg.push({ref, Value::Type::ARRAY});
		}

		if(is_string(l) && is_string(r)) {
			const auto str_l = convert::to_string(l, this->core.heap);
			const auto str_r = convert::to_string(r, this->core.heap);
			const auto ref = this->core.heap.alloc<String>({str_l + str_r});
			return this->core.reg.push({ref, Value::Type::STRING});
		}

		this->core.reg.push(calc<Addition>(l, r));
	}



	void LtnVM::sub() {
		FETCH
		this->core.reg.push(calc<Subtraction>(l, r));
	}

	void LtnVM::mlt() {
		FETCH
		this->core.reg.push(calc<Multiplication>(l, r));
	}

	void LtnVM::div() {
		FETCH
		this->core.reg.push(calc<Division>(l, r));
	}

	void LtnVM::mod() {
		FETCH
		this->core.reg.push(calc<Modulo>(l, r));
	}
}
#undef FETCH