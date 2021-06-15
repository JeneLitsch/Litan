#include "LtncFuncSearch.hxx"
#include "Unused.hxx"
ltnc::FuncSearch::FuncSearch(const FunctionSignature & signature) 
	: signature(signature) {}

const ltnc::Func * ltnc::FuncSearch::operator()(const Type & type) const {
	UNUSED(type);
	return nullptr;
}

const ltnc::Func * ltnc::FuncSearch::operator()(const Func & func) const {
	if(func == signature) {
		return &func;
	}
	return nullptr;
}

const ltnc::Func * ltnc::FuncSearch::operator()(const Var & var) const {
	UNUSED(var);
	return nullptr;
}