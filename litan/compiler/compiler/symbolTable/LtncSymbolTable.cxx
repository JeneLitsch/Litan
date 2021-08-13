#include "LtncSymbolTable.hxx"
#include <iostream>
#include "LtncTypeSearch.hxx"
#include "LtncFuncSearch.hxx"
#include "LtncVarSearch.hxx"
#include "LtncError.hxx"
#include "LtncErrorCreationCompiler.hxx"

ltn::c::SymbolTable::SymbolTable() {
	this->jumpmarkCounter = 0;
}

void ltn::c::SymbolTable::addBlockScope() {
	Scope & prev = this->scope.top();
	this->scope.push(Scope(&prev));
}

void ltn::c::SymbolTable::addFunctionScope(
	const FunctionSignature & signature) {
	this->scope.push(Scope(&this->global, signature));
}

std::string ltn::c::SymbolTable::makeJumpMark(
	const std::string & type) {
	std::string jm = type + std::to_string(this->jumpmarkCounter);
	this->jumpmarkCounter++;
	return jm;
}

void ltn::c::SymbolTable::remove() {
	this->scope.pop();
}

ltn::c::TypeId ltn::c::SymbolTable::insert(
	const DebugInfo & debugInfo,
	const Type & type) {
	try {
		return insert(type);
	}
	catch(...) {
		throw ltn::c::Error(ErrorCode::MISC, "Type is already defined: " + type.id.name, debugInfo);
	}
}



ltn::c::FunctionSignature ltn::c::SymbolTable::insert(
	const DebugInfo & debugInfo,
	const FunctionSignature & signature) {
	try {
		return insert(signature);
	}
	catch(...) {
		throw ltn::c::Error(ErrorCode::MISC, "Function " + signature.name + " is already defined in namespace " + signature.ns.str() + ".", debugInfo);
	}
}



ltn::c::VarId ltn::c::SymbolTable::insert(
	const DebugInfo & debugInfo,
	const VarId & varId,
	const TypeId & typeId) {
	try {
		return insert(varId, typeId);
	}
	catch(...) {
		throw ltn::c::Error(ErrorCode::MISC, "Var is already defined: " + varId.name, debugInfo);
	}
}



const ltn::c::Type & ltn::c::SymbolTable::match(
	const DebugInfo & debugInfo,
	const TypeId & typeId) const {
	try {
		return this->match(typeId);
	}
	catch(...) {
		throw ltn::c::Error(ErrorCode::MISC, "Type is not defined: " + typeId.name, debugInfo);
	}
}



const ltn::c::Var & ltn::c::SymbolTable::match(
	const DebugInfo & debugInfo,
	const VarId & id) const {
	try {
		return this->match(id);
	}
	catch(...) {
		throw ltn::c::Error(ErrorCode::MISC, "No matching var for: " + id.name, debugInfo);
	}
}


const ltn::c::Function & ltn::c::SymbolTable::match(
	const DebugInfo & debugInfo,
	const FunctionSignature & signature,
	bool perfectFit) const {
	try {
		return this->match(signature, perfectFit);
	}
	catch(...) {
		throw error::noMatchingFunction(debugInfo, signature);
	}
}











ltn::c::TypeId ltn::c::SymbolTable::insert(
	const Type & type) {
	TypeSearch search(type.id);
	if(this->global.find<Type>(search, true)) {
		throw std::runtime_error("");
	}
	this->global.add(type);
	return type.id;
}



ltn::c::FunctionSignature ltn::c::SymbolTable::insert(
	const FunctionSignature & signature) {
	FuncSearch search(signature, *this, true);
	if(this->global.find<Function>(search, true)) {
		throw std::runtime_error("");
	}
	Function fxInfo(signature, this->makeJumpMark("FNX_" + signature.name));
	this->global.add(fxInfo);
	return signature;
}



ltn::c::VarId ltn::c::SymbolTable::insert(
	const VarId & varId,
	const TypeId & typeId) {
	VarSearch search(varId.name);
	if(this->scope.top().find<Var>(search, false)) {
		throw std::runtime_error("");
	}
	Var var = Var(typeId, this->scope.top().countVars(), varId.name);
	this->add(var);
	return varId;
}



const ltn::c::Type & ltn::c::SymbolTable::match(
	const TypeId & typeId) const {
	TypeSearch search(typeId);
	if(auto type = this->scope.top().find<Type>(search, true)) {
		return *type;
	}
	throw ltn::Error("");
}



const ltn::c::Var & ltn::c::SymbolTable::match(
	const VarId & id) const {
	VarSearch search(id.name);
	if(auto var = this->scope.top().find<Var>(search, true)) {
		return *var;
	}
	throw ltn::Error("");
}

const ltn::c::Function & ltn::c::SymbolTable::match(
	const FunctionSignature & signature,
	bool perfectFit) const {
	FuncSearch search(signature, *this, perfectFit);
	if(auto fx = this->scope.top().find<Function>(search, true)) {
		return *fx;
	}
	throw ltn::Error("");
}






void ltn::c::SymbolTable::add(const auto & entry) {
	if(this->scope.empty()) {
		this->global.add(entry);
	}
	else {
		this->scope.top().add(entry);
	}
}



const ltn::c::FunctionSignature & ltn::c::SymbolTable::currentFxSignature() const {
	return this->scope.top().getFxSignature();
}