#include "Type.hxx"

namespace ltn::vm {
	std::string type_name(const Type & type, VMCore & core) {
		return type.name(core);
	}



	bool type_is(const Type & type, const Value & value, VMCore & core) {
		return type.is(value, core);
	}



	Value type_cast(const Type & type, const Value & value, VMCore & core) {
		try {
			return type.cast(value, core);
		}
		catch(...) {
			return value::null;
		}
	}
}