#pragma once
#include "LtncSignature.hxx"
namespace ltnc {
	struct FxInfo {
		FxInfo(FxSignature signature, std::string jumpMark)
			: signature(signature), jumpMark(jumpMark) {}
		FxSignature signature;
		std::string jumpMark;
		bool inlined = false;
		std::optional<std::string> inlineCode;
	};
}