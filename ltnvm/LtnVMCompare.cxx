#include "LtnVM.hxx"
#include "TypeCheck.hxx"

namespace ltn::vm {
	namespace {

	}

	#define FETCH\
		const auto r = this->reg.pop();\
		const auto l = this->reg.pop();

	#define COMP_II(op)\
		if(isInt(l) && isInt(r)) {\
			return this->reg.push(Value{l.i op r.i});\
		}

	#define COMP_FF(op)\
		if(isFloat(l) && isFloat(r)) {\
			return this->reg.push(Value{l.f op r.f});\
		}

	std::runtime_error cannotCompare() {
		return  std::runtime_error{"Cannot compare different type"};
	}

	void LtnVM::eql() {
		FETCH
		COMP_II(==)
		COMP_FF(==)
		throw cannotCompare();
	}
	void LtnVM::ueql() {
		FETCH
		COMP_II(!=)
		COMP_FF(!=)
		throw cannotCompare();
	}
	void LtnVM::sml() {
		FETCH
		COMP_II(<)
		COMP_FF(<)
		throw cannotCompare();
	}
	void LtnVM::bgr() {
		FETCH
		COMP_II(>)
		COMP_FF(>)
		throw cannotCompare();
	}
	void LtnVM::bgreql() {
		FETCH
		COMP_II(>=)
		COMP_FF(>=)
		throw cannotCompare();
	}
	void LtnVM::smleql() {
		FETCH
		COMP_II(<=)
		COMP_FF(<=)
		throw cannotCompare();
	}

	#undef COMP_II
	#undef COMP_FF
	#undef FETCH
}