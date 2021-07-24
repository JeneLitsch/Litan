#pragma once
#include <string>
#include "LtncNamespace.hxx"
namespace ltnc {
	class Symbol {
	public:
		Symbol(const std::string & name);
		Symbol(const std::string & name, const Namespace & ns);

		std::string name;
		Namespace ns;
	};

	inline bool operator==(const Symbol & l, const Symbol & r) {
		return (l.name == r.name) && (r.ns == l.ns);
	}
}