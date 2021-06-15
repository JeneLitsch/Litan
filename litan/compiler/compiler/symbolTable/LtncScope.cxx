#include "LtncScope.hxx"

ltnc::Scope::Scope(Scope & scope) 
	: Scope() {
	this->prev = &scope;
}


ltnc::Scope::Scope(Scope & scope, const FunctionSignature & signature) 
	: Scope() {
	this->prev = &scope; 
	this->fxSignature = signature;
}


ltnc::Scope::Scope(){
	this->prev = nullptr;
}


std::uint32_t ltnc::Scope::countVars() const {
	if(this->prev) {
		return std::uint32_t(this->counterVars) + this->prev->countVars();
	}
	return std::uint32_t(this->counterVars);
}


const ltnc::FunctionSignature & ltnc::Scope::getFxSignature() const {
	if(this->fxSignature) {
		return *this->fxSignature;
	}
	if(this->prev) {
		return this->prev->getFxSignature();
	}
	throw std::runtime_error("No fx signature found");
}


void ltnc::Scope::add(const Type & entry) {
	counterTypes++;
	this->table.push_back(Entry(entry));
}

void ltnc::Scope::add(const Function & entry) {
	counterFuncs++;
	this->table.push_back(Entry(entry));
}

void ltnc::Scope::add(const Var & entry) {
	counterVars++;
	this->table.push_back(Entry(entry));
}