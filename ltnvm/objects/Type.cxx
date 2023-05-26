#include "Type.hxx"

namespace ltn::vm {
	std::string type_name(const TypeNode & type) {
		return type.name();
	}



	bool type_is(const TypeNode & type, const Value & value, VmCore & core) {
		return type.is(value, core);
	}



	Value type_cast(const TypeNode & type, const Value & value, VmCore & core) {
		try {
			return type.cast(value, core);
		}
		catch(...) {
			return value::null;
		}
	}
}