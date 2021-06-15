#include "LtncScope.hxx"
#include "LtncDumpTable.hxx"

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
	// this->dump();
} 

// const ltnc::Type * ltnc::Scope::find(const TypeId & typeId, bool fallthrough) const {
// 	for(const Entry & entry : table) {
// 		if(auto v = std::get_if<Type>(&entry)) {
// 			if(v->id == typeId) {
// 				return v;
// 			}
// 		}
// 	}
// 	if(this->prev && fallthrough) {
// 		return this->prev->find(typeId, true);
// 	}
// 	return nullptr;
// }

// const ltnc::Func * ltnc::Scope::find(const FunctionSignature & signature, bool fallthrough) const {
// 	for(const Entry & entry : table) {
// 		if(auto v = std::get_if<Func>(&entry)) {
// 			if(v->signature == signature) {
// 				return v;
// 			}
// 		}
// 	}
// 	if(this->prev && fallthrough) {
// 		return this->prev->find(signature, true);
// 	}
// 	return nullptr;
// }

// const ltnc::Var * ltnc::Scope::find(const std::string & name, bool fallthrough) const {
// 	this->dump();
// 	for(const Entry & entry : table) {
// 		if(auto v = std::get_if<Var>(&entry)) {
// 			if(v->name == name) {
// 				return v;
// 			}
// 		}
// 	}
// 	if(this->prev && fallthrough) {
// 		return this->prev->find(name, true);
// 	}
// 	return nullptr;
// }

// void ltnc::Scope::dump() const {
// 	for(const Entry & entry : table) {
// 		if(auto v = std::get_if<Var>(&entry)) {
// 			std::cout << "var " << v->name << std::endl; 
// 		}
// 		if(auto v = std::get_if<Func>(&entry)) {
// 			std::cout << "func " << v->signature.name << std::endl; 
// 		}
// 		if(auto v = std::get_if<Type>(&entry)) {
// 			std::cout << "type " << v->id.name << std::endl; 
// 		}

// 	}
// }