#include "LtncSymbolTable.hxx"

ltnc::SymbolTable::SymbolTable() {
	this->jumpmarkCounter = 0;
}

void ltnc::SymbolTable::addBlockScope() {
	this->scope.emplace(this->get());
}

void ltnc::SymbolTable::addFunctionScope(const FxSignature & signature) {
	this->scope.emplace(signature);
}

void ltnc::SymbolTable::remove() {
	this->scope.pop();
}

ltnc::Scope & ltnc::SymbolTable::get() {
	return this->scope.top();
}

void ltnc::SymbolTable::registerType(const Type & type) {
	if(this->checkType(type.name)) {
		throw std::runtime_error("Type is already defined: " + type.name);
	}
	this->types.insert(type);
}

bool ltnc::SymbolTable::checkType(const std::string & typeName) const {
	return this->types.contains(typeName);
}


void ltnc::SymbolTable::guardType(const std::string & typeName) const {
	if(!this->checkType(typeName)) {
		throw std::runtime_error("Type is not defined: " + typeName);
	}
}


const ltnc::Type & ltnc::SymbolTable::getType(const std::string & typeName) const {
	this->guardType(typeName);
	return *this->types.find(typeName);
}


void ltnc::SymbolTable::registerFunction(const FxSignature & signature) {
	if(this->matchFunction(signature)) {
		throw std::runtime_error("Function is already defined.");
	}
	FxInfo fxInfo(signature, this->makeJumpMark("FNX_" + signature.name));
	this->fxSignatures.push_back(fxInfo);
}

std::optional<ltnc::FxInfo> ltnc::SymbolTable::matchFunction(const FxSignature & signature) const {
	for(const FxInfo & fxInfo : this->fxSignatures) {
		if(fxInfo.signature == signature) {
			return fxInfo;
		}
	}
	return {};
}

std::string ltnc::SymbolTable::makeJumpMark(std::string type) {
	std::string name = type + "_" + std::to_string(this->jumpmarkCounter);
	this->jumpmarkCounter++;
	return name;
}