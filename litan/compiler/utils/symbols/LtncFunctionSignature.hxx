#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "LtncType.hxx"
#include "LtncVar.hxx"
#include "LtncBaseTypes.hxx"
#include "LtncSymbol.hxx"

namespace ltnc {
	class FunctionSignature : public Symbol {
	public:
		FunctionSignature(
			const TypeId & returnType,
			const std::string & name,
			const std::vector<Param> & params,
			const Namespace & ns = Namespace(),
			bool ignoreRaw = false)
		:	Symbol(name, ns),
			returnType(returnType),
			params(params),
			ignoreRaw(ignoreRaw) {}

		TypeId returnType;
		std::vector<Param> params;
		bool ignoreRaw;
	};
	

	inline bool operator==(const FunctionSignature & signatureL, const FunctionSignature & signatureR) {
		if(signatureL.params.size() != signatureR.params.size()) return false;

		for(std::size_t idx = 0; idx < signatureL.params.size(); idx++){
			const Param & paramL = signatureL.params[idx];
			const Param & paramR = signatureR.params[idx];

			bool ingoreL = paramL.typeId == TRaw && signatureR.ignoreRaw;
			bool ingoreR = paramR.typeId == TRaw && signatureL.ignoreRaw;
			// skip raw ?
			if(ingoreL || ingoreR) {
				continue;
			}

			if(paramL.typeId != paramR.typeId) {
				return false;
			}
		}
		return Symbol(signatureL) == Symbol(signatureR);
	}
};
