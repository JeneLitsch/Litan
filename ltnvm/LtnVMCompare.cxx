#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include "calcBinary.hxx"
#include "Operations.hxx"
#include "compare.hxx"

namespace ltn::vm {

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

	#undef FETCH
}