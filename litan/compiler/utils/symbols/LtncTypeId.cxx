#include "LtncTypeId.hxx"

ltnc::TypeId::TypeId(const std::string & name, Namespace & ns)
	: Symbol(name, ns) {}

ltnc::TypeId::TypeId(const char * name, Namespace & ns)
	: Symbol(name, ns) {}

ltnc::TypeId::TypeId(const std::string & name)
	: Symbol(name) {}

ltnc::TypeId::TypeId(const char * name)
	: Symbol(name) {}

bool ltnc::operator==(const TypeId & l, const TypeId & r) {
	return Symbol(l) == Symbol(r);
}

std::ostream & ltnc::operator<<(std::ostream & stream, const TypeId & typeId) {
	stream << typeId.ns << typeId.name;
	return stream;
}
