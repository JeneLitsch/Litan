#pragma once 
#include <string>
#include <vector>
#include "LtncType.hxx"
#include "LtncVar.hxx"
namespace ltnc {
	class FxSignature {
	public:
		FxSignature(Type returnType, std::string name, const std::vector<Param> & params)
			: returnType(returnType), name(name), params(params) {}
		
		Type returnType;
		std::string name;
		std::vector<Param> params;
	};


	inline bool operator==(const FxSignature & signatureL, const FxSignature & signatureR) {
		if(signatureL.params.size() != signatureR.params.size()) return false;

		for(int idx = 0; idx < signatureL.params.size(); idx++){
			const Param & paramL = signatureL.params[idx];
			const Param & paramR = signatureR.params[idx];
			if(paramL.type != paramR.type) {
				return false;
			}
		}
		return signatureL.name == signatureR.name;
	}
};