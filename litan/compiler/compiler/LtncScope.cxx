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
	Var var = Var(type, this->getSize());
	if(this->vars.contains(name)){
		throw std::runtime_error("Variable already defined: " + name);
	}
	this->vars.insert({name, var});
	return var;
}

ltnc::Var ltnc::Scope::getVar(const std::string & name) const {
	if(this->vars.contains(name)){
		Var var = this->vars.at(name);
		return var;
	}
	if(this->prev) {
		return this->prev->getVar(name);
	}
	throw std::runtime_error("Variable not defined: " + name);
}

std::uint32_t ltnc::Scope::getSize() const {
	if(this->prev) {
		return this->vars.size() + this->prev->getSize();
	}
	return this->vars.size();
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
