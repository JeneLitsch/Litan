#include "LtncTypeId.hxx"

ltn::c::TypeId::TypeId(const std::string & name, Namespace & ns)
	: Symbol(name, ns) {}

ltn::c::TypeId::TypeId(const char * name, Namespace & ns)
	: Symbol(name, ns) {}

ltn::c::TypeId::TypeId(const std::string & name)
	: Symbol(name) {}

ltn::c::TypeId::TypeId(const char * name)
	: Symbol(name) {}

bool ltn::c::operator==(const TypeId & l, const TypeId & r) {
	return Symbol(l) == Symbol(r);
}

bool ltn::c::operator!=(const TypeId & l, const TypeId & r) {
	return !(l == r);
}


std::ostream & ltn::c::operator<<(std::ostream & stream, const TypeId & typeId) {
	stream << typeId.ns << typeId.name;
	return stream;
}
