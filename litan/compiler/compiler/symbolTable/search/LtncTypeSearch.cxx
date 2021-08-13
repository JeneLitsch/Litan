#include "LtncTypeSearch.hxx"
#include "Unused.hxx"

ltn::c::TypeSearch::TypeSearch(const TypeId & typeId) 
	: typeId(typeId) {}

const ltn::c::Type * ltn::c::TypeSearch::operator()(const Type & type) const {
	if(type == typeId) {
		return &type;
	}
	return nullptr;
}

const ltn::c::Type * ltn::c::TypeSearch::operator()(const Function & func) const {
	UNUSED(func);
	return nullptr;
}

const ltn::c::Type * ltn::c::TypeSearch::operator()(const Var & var) const {
	UNUSED(var);
	return nullptr;
}