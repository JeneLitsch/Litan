#include "LtnVM.hxx"
#include <cmath>
#include "TypeCheck.hxx"

namespace ltn::vm {

	namespace {
		template<class T>
		std::vector<T> operator+(const std::vector<T> & l, const std::vector<T> & r) {
			std::vector<T> vec;
			vec.reserve(l.size() + r.size());
			vec.insert(std::end(vec), l.begin(), l.end());
			vec.insert(std::end(vec), r.begin(), r.end());
			return vec;
		}
	}

	#define FETCH\
		const auto r = this->reg.pop();\
		const auto l = this->reg.pop();

	#define BIN_II(op)\
		if(isInt(l) && isInt(r)) {\
			return this->reg.push(Value{l.i op r.i});\
		}

	#define BIN_FF(op)\
		if(isFloat(l) && isFloat(r)) {\
			return this->reg.push(Value{l.f op r.f});\
		}

	#define BIN_FX_FF(op)\
		if(isFloat(l) && isFloat(r)) {\
			return this->reg.push(Value{op(l.f, r.f)});\
		}

	void LtnVM::add() { 
		FETCH
		BIN_II(+)
		BIN_FF(+)
		if(isArr(l) && isArr(r)) {
			const auto arrL = this->heap.readArray(l.u);
			const auto arrR = this->heap.readArray(r.u);
			const auto ref = this->heap.allocArray();
			auto & arr = this->heap.readArray(ref);
			arr = arrL + arrR;
			return this->reg.push({ref, Value::Type::ARRAY});
		}
		throw std::runtime_error{"Cannot add types"};
	}
	void LtnVM::sub() {
		FETCH
		BIN_II(-)
		BIN_FF(-)
		throw std::runtime_error{"Cannot subtract types"};
	}
	void LtnVM::mlt() {
		FETCH
		BIN_II(*)
		BIN_FF(*)
		throw std::runtime_error{"Cannot multiply types"};
	}
	void LtnVM::div() {
		FETCH
		BIN_II(/)
		BIN_FF(/)
		throw std::runtime_error{"Cannot divide types"};
	}
	void LtnVM::mod() {
		FETCH
		BIN_II(%)
		BIN_FX_FF(std::fmod)
		throw std::runtime_error{"Cannot mod types"};
	}

	#undef FETCH
	#undef BIN_II
	#undef BIN_FF
	#undef BIN_FX_FF
}