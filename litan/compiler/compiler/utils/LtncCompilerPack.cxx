#include "LtncCompilerPack.hxx"
#include <iostream>
ltnc::CompilerPack::CompilerPack(const CompilerSettings & settings) 
	: settings(settings) {
	this->jumpmarkCounter = 0;
}

void ltnc::CompilerPack::registerFunction(const std::shared_ptr<DeclFunction> & fx) {
	if(this->matchFunction(fx->signature)) {
		throw std::runtime_error("Function is already defined.");
	}
	FxInfo fxInfo(fx->signature, this->makeJumpMark("FNX_" + fx->signature.name));
	fxInfo.inlined = fx->inlined;
	this->fxSignatures.push_back(fxInfo);
}

std::optional<ltnc::FxInfo> ltnc::CompilerPack::matchFunction(const FxSignature & signature) const {
	for(const FxInfo & fxInfo : this->fxSignatures) {
		if(fxInfo.signature == signature) {
			return fxInfo;
		}
	}
	return {};
}

void ltnc::CompilerPack::addInlineCode(
	const FxSignature & signature,
	const std::string & code) {
	for(FxInfo & fxInfo : this->fxSignatures) {
		if(fxInfo.signature == signature) {
			fxInfo.inlineCode = code;
		}
	}
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

const ltnc::TypeTable & ltnc::CompilerPack::getTypeTable() const {
	return this->typeTable;
}

ltnc::TypeTable & ltnc::CompilerPack::getTypeTable(){
	return this->typeTable;
}

const ltnc::CompilerSettings & ltnc::CompilerPack::getSettings() const {
	return this->settings;
}
