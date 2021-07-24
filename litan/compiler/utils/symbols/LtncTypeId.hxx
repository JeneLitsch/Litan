#pragma once
#include "LtncSymbol.hxx"
namespace ltnc {
	struct TypeId : public Symbol {
		TypeId(const std::string & name, Namespace & ns)
			: Symbol(name, ns) {}

		TypeId(const char * name, Namespace & ns)
			: Symbol(name, ns) {}

		TypeId(const std::string & name)
			: Symbol(name) {}

		TypeId(const char * name)
			: Symbol(name) {}
	};

	inline bool operator==(const TypeId & l, const TypeId & r) {
		return Symbol(l) == Symbol(r);
	}
}