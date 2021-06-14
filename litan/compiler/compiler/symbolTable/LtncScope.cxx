#include "LtncScope.hxx"

ltnc::Scope::Scope(Scope & scope) 
	: Scope() {
	this->prev = &scope;
}


ltnc::Scope::Scope(const FxSignature & signature) 
	: Scope() {
	this->fxSignature = signature;
}


ltnc::Scope::Scope(){
	this->prev = nullptr;
	this->vars = {};
}


ltnc::Var ltnc::Scope::registerVar(const std::string & name, Type type){
	Var var = Var(type.name, this->countVars(), name);
	if(this->vars.contains(name)){
		throw std::runtime_error("Variable already defined: " + name);
	}
	this->vars.insert({var});
	return var;
}


ltnc::Var ltnc::Scope::getVar(const std::string & name) const {
	if(this->vars.contains(name)){
		Var var = *this->vars.find(name);
		return var;
	}
	if(this->prev) {
		return this->prev->getVar(name);
	}
	throw std::runtime_error("Variable not defined: " + name);
}


std::uint32_t ltnc::Scope::countVars() const {
	if(this->prev) {
		return std::uint32_t(this->vars.size()) + this->prev->countVars();
	}
	return std::uint32_t(this->vars.size());
}


const ltnc::FxSignature & ltnc::Scope::getFxSignature() const {
	if(this->fxSignature) {
		return *this->fxSignature;
	}
	if(this->prev) {
		return this->prev->getFxSignature();
	}
	throw std::runtime_error("No fx signature found");
}
