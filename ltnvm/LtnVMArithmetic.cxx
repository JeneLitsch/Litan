#include "LtnVM.hxx"
#include <cmath>
#include "TypeCheck.hxx"
#include <sstream>
#include "cast.hxx"
#include "Operations.hxx"
#include "calcBinary.hxx"

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
			const auto & strL = heap.read<String>(l.u).get();
			const auto strR = cast::to_string(r, heap);
			const auto ref = heap.alloc<String>({strL + strR});
			return this->reg.push({ref, Value::Type::STRING});
		}

		if(isArr(r)) {
			const auto arrR = heap.read<Array>(r.u);
			const auto ref = heap.alloc<Array>({std::vector{l} + arrR.arr});
			return this->reg.push({ref, Value::Type::ARRAY});
		}

		if(isStr(r)) {
			const auto strL = cast::to_string(l, heap);
			const auto & strR = heap.read<String>(r.u).get();
			const auto ref = heap.alloc<String>({strL + strR});
			return this->reg.push({ref, Value::Type::STRING});
		}

		this->reg.push(calc<Addition>(l, r));
	}



	void LtnVM::sub() {
		FETCH
		this->reg.push(calc<Subtraction>(l, r));
	}

	void LtnVM::mlt() {
		FETCH
		this->reg.push(calc<Multiplication>(l, r));
	}

	void LtnVM::div() {
		FETCH
		this->reg.push(calc<Division>(l, r));
	}

	void LtnVM::mod() {
		FETCH
		this->reg.push(calc<Modulo>(l, r));
	}

	void LtnVM::shift_l() {
		FETCH
		if(isInt(l) && isInt(r)) {
			return this->reg.push(Value{l.i << r.i});
		}
		throw except::invalidOperands();
	}

	void LtnVM::shift_r() {
		FETCH
		if(isInt(l) && isInt(r)) {
			return this->reg.push(Value{l.i >> r.i});
		}
		throw except::invalidOperands();
	}

	#undef FETCH
}