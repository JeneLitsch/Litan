#include "Variable.hxx"

namespace ltn::c::compile {
	bool isConst(const Variable & var) {
		return var.qualifier == Variable::Qualifier::CONST;
	}

	bool isMutable(const Variable & var) {
		return var.qualifier == Variable::Qualifier::MUTABLE;
	}
}