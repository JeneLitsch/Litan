#include "LtncCompilerPack.hxx"
#include <iostream>
ltnc::CompilerPack::CompilerPack() {
	this->jumpmarkCounter = 0;
}

void ltnc::CompilerPack::registerFunction(const std::shared_ptr<DeclFunction> & fx) {
	if(this->matchFunction(fx->signature)) {
		throw std::runtime_error("Function is already defined.");
	}
	this->fxSignatures.push_back(FxInfo(fx->signature, this->makeJumpMark("FNX_" + fx->signature.name)));
}

std::optional<ltnc::FxInfo> ltnc::CompilerPack::matchFunction(const FxSignature & signature) const {
	for(const FxInfo & fxInfo : this->fxSignatures) {
		if(fxInfo.signature == signature) {
			return fxInfo;
		}
	}
	return {};
}

std::string ltnc::CompilerPack::makeJumpMark(std::string type) {
	std::string name = type + "_" + std::to_string(this->jumpmarkCounter);
	this->jumpmarkCounter++;
	return name;
}

const ltnc::ScopeStack & ltnc::CompilerPack::getScopes() const {
	return this->scopeStack;
}

ltnc::ScopeStack & ltnc::CompilerPack::getScopes(){
	return this->scopeStack;
}
