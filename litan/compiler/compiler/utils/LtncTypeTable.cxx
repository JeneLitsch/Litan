#include "LtncTypeTable.hxx"

void ltnc::TypeTable::registerType(const Type & type) {
	if(this->types.contains(type)) {
		throw std::runtime_error("Type is already defined: " + type.name);
	}
	this->types.insert(type);
}

bool ltnc::TypeTable::checkType(const std::string & typeName) const {
	return this->types.contains(typeName);
}


void ltnc::TypeTable::guardType(const std::string & typeName) const {
	if(!this->checkType(typeName)) {
		throw std::runtime_error("Type is not defined: " + typeName);
	}
}


const ltnc::Type & ltnc::TypeTable::getType(const std::string & typeName) const {
	this->guardType(typeName);
	return *this->types.find(typeName);
}
