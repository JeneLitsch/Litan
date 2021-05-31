#include "LtncTypeTable.hxx"

void ltnc::TypeTable::registerType(const std::string & typeName) {
	if(this->types.contains(typeName)) {
		throw std::runtime_error("Type is already defined: " + typeName);
	}
	this->types.insert(typeName);
}

bool ltnc::TypeTable::checkType(const Type & type) const {
	return this->types.contains(type.typeName);
}


void ltnc::TypeTable::guardType(const Type & type) const {
	if(!this->checkType(type)) {
		throw std::runtime_error("Type is not defined: " + type.typeName);
	}
}
