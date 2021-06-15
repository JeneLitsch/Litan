#include "LtncTypeSearch.hxx"
#include "Unused.hxx"

ltnc::TypeSearch::TypeSearch(const TypeId & typeId) 
	: typeId(typeId) {}

const ltnc::Type * ltnc::TypeSearch::operator()(const Type & type) const {
	if(type == typeId) {
		return &type;
	}
	return nullptr;
}

const ltnc::Type * ltnc::TypeSearch::operator()(const Func & func) const {
	UNUSED(func);
	return nullptr;
}

const ltnc::Type * ltnc::TypeSearch::operator()(const Var & var) const {
	UNUSED(var);
	return nullptr;
}
