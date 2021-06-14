#include "LtncSymbolTable.hxx"
#include <iostream>
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

void ltnc::SymbolTable::insert(const Type & type) {
	if(this->checkType(type.name)) {
		throw std::runtime_error("Type is already defined: " + type.name);
	}
	this->types.push_back(type);
}

bool ltnc::SymbolTable::checkType(const std::string & typeName) const {
	return this->find(typeName) != nullptr;
}


void ltnc::SymbolTable::guardType(const std::string & typeName) const {
	if(!this->checkType(typeName)) {
		throw std::runtime_error("Type is not defined: " + typeName);
	}
}


const ltnc::Type & ltnc::SymbolTable::match(const std::string & typeName) const {
	if(auto type = this->find(typeName)) {
		return *type;
	}
	throw std::runtime_error("Type is not defined: " + typeName);
}


void ltnc::SymbolTable::insert(const FxSignature & signature) {
	if(this->find(signature)) {
		throw std::runtime_error("Function is already defined.");
	}
	FxInfo fxInfo(signature, this->makeJumpMark("FNX_" + signature.name));
	this->fxs.push_back(fxInfo);
}

const ltnc::FxInfo & ltnc::SymbolTable::match(const FxSignature & signature) const {
	if(auto fx = this->find(signature)) {
		return *fx;
	}
	throw std::runtime_error("No matching function for: " + signature.name);
}

std::string ltnc::SymbolTable::makeJumpMark(std::string type) {
	std::string name = type + "_" + std::to_string(this->jumpmarkCounter);
	this->jumpmarkCounter++;
	return name;
}

const ltnc::Type * ltnc::SymbolTable::find(const std::string & typeName) const {
	for(const auto & type : this->types) {
		if(type == typeName) {
			return &type;
		}
	}
	return nullptr;
}


const ltnc::FxInfo * ltnc::SymbolTable::find(const FxSignature & signature) const {
	for(const auto & fx : this->fxs) {
		if(fx == signature) {
			return &fx;
		}
	}
	return nullptr;
}