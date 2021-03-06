#include "Variable.hxx"

namespace ltn::c {
	bool is_const(const Variable & var) {
		return var.qualifier == Variable::Qualifier::CONST;
	}

	bool is_mutable(const Variable & var) {
		return var.qualifier == Variable::Qualifier::MUTABLE;
	}
}