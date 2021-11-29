#include "LtnVM.hxx"
#include <cmath>
#include "TypeCheck.hxx"
#include <sstream>
#include "Stringify.hxx"
#include "Operations.hxx"
#include "CalcBinary.hxx"

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

		#define FETCH\
			const auto r = this->reg.pop();\
			const auto l = this->reg.pop();

		Array toArray(const Value & value, Heap & heap) {
			if(isArr(value)) {
				return heap.read<Array>(value.u);
			}
			return {{value}};
		}
	}


	void LtnVM::add() {
		FETCH
		
		if(isArr(l)) {
			const auto & arrL = heap.read<Array>(l.u);
			const auto & arrR = toArray(r, heap);
			const auto ref = heap.alloc<Array>({arrL.arr + arrR.arr});
			return this->reg.push({ref, Value::Type::ARRAY});
		}

		if(isStr(l)) {
			const auto & strL = heap.read<String>(l.u);
			const auto ref = heap.alloc<String>({strL.str + toString(r, heap)});
			return this->reg.push({ref, Value::Type::STRING});
		}

		if(isArr(r)) {
			const auto arrR = heap.read<Array>(r.u);
			const auto ref = heap.alloc<Array>({std::vector{l} + arrR.arr});
			return this->reg.push({ref, Value::Type::ARRAY});
		}

		if(isStr(r)) {
			const auto & strR = heap.read<String>(r.u);
			const auto ref =heap.alloc<String>({toString(l, heap) + strR.str});
			return this->reg.push({ref, Value::Type::STRING});
		}

		constexpr auto msg = "Not operator + for types";
		this->reg.push(calc<Addition>(l, r, msg));
	}



	void LtnVM::sub() {
		FETCH
		constexpr auto msg = "Not operator - for types";
		this->reg.push(calc<Subtraction>(l, r, msg));
	}

	void LtnVM::mlt() {
		FETCH
		constexpr auto msg = "Not operator * for types";
		this->reg.push(calc<Multiplication>(l, r, msg));
	}

	void LtnVM::div() {
		FETCH
		constexpr auto msg =  "Not operator / for types";
		this->reg.push(calc<Division>(l, r, msg));
	}

	void LtnVM::mod() {
		FETCH
		constexpr auto msg = "Not operator % for types";
		this->reg.push(calc<Modulo>(l, r, msg));
	}

	void LtnVM::shift_l() {
		FETCH
		if(isInt(l) && isInt(r)) {
			return this->reg.push(Value{l.i << r.i});
		}
		throw std::runtime_error{"Only ints can be bit-shifted"};
	}

	void LtnVM::shift_r() {
		FETCH
		if(isInt(l) && isInt(r)) {
			return this->reg.push(Value{l.i >> r.i});
		}
		throw std::runtime_error{"Only ints can be bit-shifted"};
	}

	#undef FETCH
}