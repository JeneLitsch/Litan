#include "LtncFuncSearch.hxx"
#include "Unused.hxx"
#include "LtncSymbolTable.hxx"

namespace ltnc {
	bool compare(
		const FunctionSignature & signatureL,
		const FunctionSignature & signatureR) {
		
		if(signatureL.params.size() != signatureR.params.size()) return false;

		for(std::size_t idx = 0; idx < signatureL.params.size(); idx++){
			const Param & paramL = signatureL.params[idx];
			const Param & paramR = signatureR.params[idx];

			if(paramL.typeId != paramR.typeId) {
				return false;
			}
		}
		return Symbol(signatureL) == Symbol(signatureR);
	}

	bool compare(
		const FunctionSignature & signatureL,
		const FunctionSignature & signatureR,
		const SymbolTable & sTable) {

		if(signatureL.params.size() != signatureR.params.size()) return false;

		for(std::size_t idx = 0; idx < signatureL.params.size(); idx++){
			const Param & paramL = signatureL.params[idx];
			const Param & paramR = signatureR.params[idx];
			const Type & typeL = sTable.match(paramL.typeId);
			const Type & typeR = sTable.match(paramR.typeId);

			bool ingore = typeL.isCastableTo(typeR.id);

			if(paramL.typeId != paramR.typeId && !ingore) {
				return false;
			}
		}
		return Symbol(signatureL) == Symbol(signatureR);
	}
}

ltnc::FuncSearch::FuncSearch(const FunctionSignature & signature, const SymbolTable & sTable, bool perfectFit) 
	: signature(signature), sTable(sTable), perfectFit(perfectFit) {}

const ltnc::Func * ltnc::FuncSearch::operator()(const Type & type) const {
	UNUSED(type);
	return nullptr;
}

const ltnc::Func * ltnc::FuncSearch::operator()(const Func & func) const {
	if(this->perfectFit) {
		if(compare(this->signature, func.signature)) {
			return &func;
		}
	}
	else {
		if(compare(this->signature, func.signature, this->sTable)) {
			return &func;
		}
	}
	return nullptr;
}

const ltnc::Func * ltnc::FuncSearch::operator()(const Var & var) const {
	UNUSED(var);
	return nullptr;
}