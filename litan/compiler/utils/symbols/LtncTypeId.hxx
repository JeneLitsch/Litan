#pragma once
#include "LtncSymbol.hxx"
namespace ltnc {
	struct TypeId : public Symbol {
		TypeId(const std::string & name, Namespace & ns);
		TypeId(const char * name, Namespace & ns);
		TypeId(const std::string & name);
		TypeId(const char * name);
	};

	bool operator==(const TypeId & l, const TypeId & r);
	bool operator!=(const TypeId & l, const TypeId & r);
	std::ostream & operator<<(std::ostream & stream, const TypeId & typeId);

}