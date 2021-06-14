#pragma once
#include "LtncSignature.hxx"
namespace ltnc {
	struct FxInfo {
		FxInfo(FxSignature signature, std::string jumpMark)
			: signature(signature), jumpMark(jumpMark) {}
		FxSignature signature;
		std::string jumpMark;
	};


	inline bool operator==(const FxInfo & fxL, const FxInfo & fxR) {
		return fxL.signature == fxR.signature;
	}

	inline bool operator==(const FxInfo & fx, const FxSignature & signature) {
		return fx.signature == signature;
	}
	
	inline bool operator==(const FxSignature & signature, const FxInfo & fx) {
		return signature == fx.signature;
	}



	inline bool operator<(const FxInfo & fxL, const FxInfo & fxR) {
		return fxL.signature < fxR.signature;
	}
	
	inline bool operator<(const FxInfo & fx, const FxSignature & signature) {
		return fx.signature < signature;
	}
	
	inline bool operator<(const FxSignature & signature, const FxInfo & fx) {
		return signature < fx.signature;
	}



	inline bool operator>(const FxInfo & fxL, const FxInfo & fxR) {
		return fxL.signature > fxR.signature;
	}
	
	inline bool operator>(const FxInfo & fx, const FxSignature & signature) {
		return fx.signature > signature;
	}
	
	inline bool operator>(const FxSignature & signature, const FxInfo & fx) {
		return signature > fx.signature;
	}
}