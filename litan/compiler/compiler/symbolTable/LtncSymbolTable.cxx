#include "LtncSymbolTable.hxx"
#include <iostream>
#include "LtncTypeSearch.hxx"
#include "LtncFuncSearch.hxx"
#include "LtncVarSearch.hxx"

ltnc::SymbolTable::SymbolTable() {
	this->jumpmarkCounter = 0;
}

void ltnc::SymbolTable::addBlockScope() {
	Scope & prev = this->scope.top();
	this->scope.push(Scope(&prev));
}

void ltnc::SymbolTable::addFunctionScope(const FunctionSignature & signature) {
	this->scope.push(Scope(&this->global, signature));
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
	FuncSearch search(signature, *this, true);
	if(this->global.find<Func>(search, true)) {
		throw std::runtime_error("Function " + signature.name + " is already defined in namespace " + signature.ns.str() + ".");
	}
	Function fxInfo(signature, this->makeJumpMark("FNX_" + signature.name));
	this->global.add(fxInfo);
	return signature;
}



ltnc::VarId ltnc::SymbolTable::insert(const VarId & varId, const TypeId & typeId) {
	VarSearch search(varId.name);
	if(this->scope.top().find<Var>(search, false)) {
		throw std::runtime_error("Var is already defined: " + varId.name);
	}
	Var var = Var(typeId, this->scope.top().countVars(), varId.name);
	this->add(var);
	return varId;
}

void ltnc::SymbolTable::add(const auto & entry) {
	if(this->scope.empty()) {
		this->global.add(entry);
	}
	else {
		this->scope.top().add(entry);
	}
}

const ltnc::Type & ltnc::SymbolTable::match(const TypeId & typeId) const {
	TypeSearch search(typeId);
	if(auto type = this->scope.top().find<Type>(search, true)) {
		return *type;
	}
	throw std::runtime_error("Type is not defined: " + typeId.name);
}



const ltnc::Function & ltnc::SymbolTable::match(
	const FunctionSignature & signature,
	bool perfectFit) const {
	FuncSearch search(signature, *this, perfectFit);
	if(auto fx = this->scope.top().find<Func>(search, true)) {
		return *fx;
	}
	throw std::runtime_error("No matching function for: " + signature.name + " in namespace: " + signature.ns.str());
}



const ltnc::Var & ltnc::SymbolTable::match(const VarId & id) const {
	VarSearch search(id.name);
	if(auto var = this->scope.top().find<Var>(search, true)) {
		return *var;
	}
	throw std::runtime_error("No matching var for: " + id.name);
}

const ltnc::FunctionSignature & ltnc::SymbolTable::currentFxSignature() const {
	return this->scope.top().getFxSignature();
}