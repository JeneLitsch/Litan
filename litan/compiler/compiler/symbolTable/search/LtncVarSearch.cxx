#include "LtncVarSearch.hxx"
#include "Unused.hxx"

ltnc::VarSearch::VarSearch(const std::string & name) 
	: name(name) {}

const ltnc::Var * ltnc::VarSearch::operator()(const Type & type) const {
	UNUSED(type);
	return nullptr;
}

const ltnc::Var * ltnc::VarSearch::operator()(const Func & func) const {
	UNUSED(func);
	return nullptr;
}

const ltnc::Var * ltnc::VarSearch::operator()(const Var & var) const {
	if(var == this->name) {
		return &var;
	}
	return nullptr;
}
