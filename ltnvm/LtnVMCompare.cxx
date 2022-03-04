#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include "calcBinary.hxx"
#include "Operations.hxx"
#include "compare.hxx"

namespace ltn::vm {

	
	namespace {
		Value eval_3_way(std::partial_ordering order) {
			if(order == 0) return value::integer(0);
			if(order <  0) return value::integer(-1);
			if(order >  0) return value::integer(1);
			throw except::invalid_operands(); 
		}
	}
	
	#define FETCH\
		const auto r = this->reg.pop();\
		const auto l = this->reg.pop();

	void LtnVM::eql() {
		FETCH
		return this->reg.push(compare(l, r, this->heap) == 0);
	}
	void LtnVM::ueql() {
		FETCH
		return this->reg.push(compare(l, r, this->heap) != 0);
	}
	void LtnVM::sml() {
		FETCH
		return this->reg.push(compare(l, r, this->heap) < 0);
	}
	void LtnVM::bgr() {
		FETCH
		return this->reg.push(compare(l, r, this->heap) > 0);
	}
	void LtnVM::smleql() {
		FETCH
		return this->reg.push(compare(l, r, this->heap) <= 0);
	}
	void LtnVM::bgreql() {
		FETCH
		return this->reg.push(compare(l, r, this->heap) >= 0);
	}
	void LtnVM::comp() {
		FETCH
		const auto result = compare(l, r, this->heap);
		return this->reg.push(eval_3_way(result));
	}

	#undef FETCH
}