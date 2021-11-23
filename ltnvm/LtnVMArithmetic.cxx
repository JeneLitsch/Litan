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

	struct modulo {
		auto operator()(auto l, auto r) {
			constexpr bool isI =
				std::same_as<decltype(l), std::int64_t> &&
				std::same_as<decltype(r), std::int64_t>; 
			if(r != 0) {
				if constexpr(isI) {
					return l%r;
				}
				else {
					return std::fmod(l, r);
				}
			}
			throw std::runtime_error{"Modulo by 0"};
		}
	};

	struct division {
		auto operator()(auto l, auto r) {
			using T = decltype(l/r);
			if(r != 0) {
				return static_cast<T>(l) / static_cast<T>(r);
			}
			throw std::runtime_error{"Division by 0"};
		}
	};

	#define FETCH\
		const auto r = this->reg.pop();\
		const auto l = this->reg.pop();

	std::runtime_error typeError(
		const Value &,
		const Value &,
		const std::string_view & str) {
		return std::runtime_error{ static_cast<std::string>(str) };
	}


	template<class OP>
	Value arith(const Value & l, const Value & r, const std::string_view & msg) {
		if(isBool(l)) {
			if(isBool(r)) {
				return { static_cast<std::int64_t>(OP()(l.b, r.b))};
			}
			if(isInt(r)) {
				return {OP()(l.b, r.i)};
			}
			if(isFloat(r)) {
				return {OP()(l.b, r.f)};
			}
		}
		if(isInt(l)) {
			if(isBool(r)) {
				return {OP()(l.i, r.b)};
			}
			if(isInt(r)) {
				return {OP()(l.i, r.i)};
			}
			if(isFloat(r)) {
				return {OP()(l.i, r.f)};
			}
		}
		if(isFloat(l)) {
			if(isBool(r)) {
				return {OP()(l.f, r.b)};
			}
			if(isInt(r)) {
				return {OP()(l.f, r.i)};
			}
			if(isFloat(r)) {
				return {OP()(l.f, r.f)};
			}
		}
		throw typeError(l, r, msg);
	}

	constexpr auto arithAdd = arith<std::plus<void>>;
	constexpr auto arithSub = arith<std::minus<void>>;
	constexpr auto arithMlt = arith<std::multiplies<void>>;
	constexpr auto arithDiv = arith<division>;
	constexpr auto arithMod = arith<modulo>;

	void LtnVM::add() { 
		FETCH
		if(isArr(l)) {
			const auto arrL = heap.readArray(l.u);
			if(isArr(r)) {
				const auto arrR = heap.readArray(r.u);
				const auto ref = heap.allocArray();
				auto & arr = heap.readArray(ref);
				arr = arrL + arrR;
				return this->reg.push({ref, Value::Type::ARRAY});
			}
			else {
				const auto ref = heap.allocArray();
				auto & arr = heap.readArray(ref);
				arr = arrL;
				arr.push_back(r);
				return this->reg.push({ref, Value::Type::ARRAY});
			}
		}
		if(isArr(r)) {
			const auto arrR = heap.readArray(r.u);
			const auto ref = heap.allocArray();
			auto & arr = heap.readArray(ref);
			arr = arrR;
			arr.insert(arr.begin(), l);
			return this->reg.push({ref, Value::Type::ARRAY});
		}
		this->reg.push(arithAdd(l, r, "Not operator + for types"));
	}



	void LtnVM::sub() {
		FETCH
		this->reg.push(arithSub(l, r, "Not operator - for types"));
	}

	void LtnVM::mlt() {
		FETCH
		this->reg.push(arithMlt(l, r, "Not operator * for types"));
	}

	void LtnVM::div() {
		FETCH
		this->reg.push(arithDiv(l, r, "Not operator / for types"));
	}

	void LtnVM::mod() {
		FETCH
		this->reg.push(arithMod(l, r, "Not operator % for types"));
	}



	#undef FETCH
	#undef BIN_II
	#undef BIN_FF
	#undef BIN_FX_FF
}