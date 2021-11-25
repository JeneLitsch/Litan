#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include "CalcBinary.hxx"
#include "Operations.hxx"

namespace ltn::vm {

	#define FETCH\
		const auto r = this->reg.pop();\
		const auto l = this->reg.pop();

	void LtnVM::eql() {
		FETCH
		return this->reg.push(calc<Equality>(l, r, "cannot compare =="));
	}
	void LtnVM::ueql() {
		FETCH
		return this->reg.push(calc<UnEquality>(l, r, "cannot compare !="));
	}
	void LtnVM::sml() {
		FETCH
		return this->reg.push(calc<Less>(l, r, "cannot compare <"));
	}
	void LtnVM::bgr() {
		FETCH
		return this->reg.push(calc<Greater>(l, r, "cannot compare >"));
	}
	void LtnVM::smleql() {
		FETCH
		return this->reg.push(calc<LessEqual>(l, r, "cannot compare <="));
	}
	void LtnVM::bgreql() {
		FETCH
		return this->reg.push(calc<GreaterEqual>(l, r, "cannot compare >="));
	}

	#undef FETCH
}