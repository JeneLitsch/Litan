#include "LtnVM.hxx"
#include "type_check.hxx"
#include "calcBinary.hxx"
#include "Operations.hxx"
#include "compare.hxx"
#include "convert.hxx"

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

	void LtnVM::approx() {
		static constexpr stx::float64_t max = std::numeric_limits<stx::float64_t>::max();
		static constexpr stx::float64_t eps = std::numeric_limits<stx::float64_t>::epsilon();
		FETCH
		if(is_numeric(l) || is_numeric(r)) {
			const stx::float64_t r_float = convert::to_float(r);
			const stx::float64_t l_float = convert::to_float(l);
			const stx::float64_t diff = std::abs(l_float - r_float);
			const stx::float64_t norm = std::min((l_float + r_float), max);
			const bool is_sameish = diff < (norm * eps);
			return this->reg.push(value::boolean(is_sameish)); 
		}
		else {
			const bool is_sameish = compare(l, r, this->heap) == 0;
			return this->reg.push(value::boolean(is_sameish)); 
		}
	}

	#undef FETCH
}