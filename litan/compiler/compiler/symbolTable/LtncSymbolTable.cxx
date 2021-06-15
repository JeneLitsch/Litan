#include "LtncSymbolTable.hxx"
#include <iostream>
#include "LtncTypeSearch.hxx"
#include "LtncFuncSearch.hxx"
#include "LtncVarSearch.hxx"

ltnc::SymbolTable::SymbolTable() {
	this->jumpmarkCounter = 0;
}

void ltnc::SymbolTable::addBlockScope() {
	this->scope.emplace(this->scope.top());
}

void ltnc::SymbolTable::addFunctionScope(const FunctionSignature & signature) {
	this->scope.emplace(this->global, signature);
}

std::string ltnc::SymbolTable::makeJumpMark(const std::string & type) {
	std::string jm = type + std::to_string(this->jumpmarkCounter);
	this->jumpmarkCounter++;
	return jm;
}

void ltnc::SymbolTable::remove() {
	this->scope.pop();
}

ltnc::TypeId ltnc::SymbolTable::insert(const Type & type) {
	TypeSearch search(type.id);
	if(this->global.find<Type>(search, true)) {
		throw std::runtime_error("Type is already defined: " + type.id.name);
	}
	this->global.add(type);
	return type.id;
}



ltnc::FunctionSignature ltnc::SymbolTable::insert(const FunctionSignature & signature) {
	FuncSearch search(signature);
	if(this->global.find<Func>(search, true)) {
		throw std::runtime_error("Function is already defined.");
	}
	Function fxInfo(signature, this->makeJumpMark("FNX_" + signature.name));
	this->global.add(fxInfo);
	return signature;
}



std::string ltnc::SymbolTable::insert(const std::string & name, const TypeId & typeId) {
	VarSearch search(name);
	if(this->scope.top().find<Var>(search, false)) {
		throw std::runtime_error("Var is already defined: " + name);
	}
	Var var = Var(typeId, this->scope.top().countVars(), name);
	this->scope.top().add(var);
	return name;
}



const ltnc::Type & ltnc::SymbolTable::match(const TypeId & typeId) const {
	TypeSearch search(typeId);
	if(auto type = this->scope.top().find<Type>(search, true)) {
		return *type;
	}
	throw std::runtime_error("Type is not defined: " + typeId.name);
}



const ltnc::Function & ltnc::SymbolTable::match(const FunctionSignature & signature) const {
	FuncSearch search(signature);
	if(auto fx = this->scope.top().find<Func>(search, true)) {
		return *fx;
	}
	throw std::runtime_error("No matching function for: " + signature.name);
}



const ltnc::Var & ltnc::SymbolTable::match(const std::string & name) const {
	VarSearch search(name);
	if(auto var = this->scope.top().find<Var>(search, true)) {
		return *var;
	}
	throw std::runtime_error("No matching var for: " + name);
}



const ltnc::FunctionSignature & ltnc::SymbolTable::currentFxSignature() const {
	return this->scope.top().getFxSignature();
}