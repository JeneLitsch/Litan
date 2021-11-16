#include "Type.hxx"
#include <ostream>
#include "ltn/printing.hxx"
#include "Primitives.hxx"
namespace ltn::c::type {
	bool operator==(const Type & l, const Type & r) {
		if(l.name == r.name) {
			if(l.contained.size() == r.contained.size()) {
				for(std::size_t i = 0; i < l.contained.size(); i++) {
					if(l.contained[i] != r.contained[i]) {
						return false;
					}
				}
				return true;
			}
			return false;
		} 
		return false;
	}

	bool operator!=(const Type & l, const Type & r) {
		return !(l == r);
	}

	std::ostream & operator<<(std::ostream & out, const Type & type) {
		out << type.name;
		printArray(out, type.contained);
		return out;
	}

	bool isPrimitive(const Type & type, const std::string_view & name) {
		return (type.name == name) && type.contained.empty();
	}

	bool isVoid(const Type & type) {
		return isPrimitive(type, TVoid);
	}

	bool isInt(const Type & type) {
		return isPrimitive(type, TInt);
	}

	bool isFloat(const Type & type) {
		return isPrimitive(type, TFloat);
	}

	bool isBool(const Type & type) {
		return isPrimitive(type, TBool);
	}
}