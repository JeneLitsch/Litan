#include "LtncVarSearch.hxx"
#include "Unused.hxx"

ltn::c::VarSearch::VarSearch(const std::string & name) 
	: name(name) {}

const ltn::c::Var * ltn::c::VarSearch::operator()(const Type & type) const {
	UNUSED(type);
	return nullptr;
}

const ltn::c::Var * ltn::c::VarSearch::operator()(const Function & func) const {
	UNUSED(func);
	return nullptr;
}

const ltn::c::Var * ltn::c::VarSearch::operator()(const Var & var) const {
	if(var == this->name) {
		return &var;
	}
	return nullptr;
}
