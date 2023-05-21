#include "Type.hxx"

namespace ltn::vm {
	std::string type_name(const TypeNode & type) {
		return type.name();
	}



	bool type_is(const TypeNode & type, const Value & value, Heap & heap) {
		return type.is(value, heap);
	}



	Value type_cast(const TypeNode & type, const Value & value, Heap & heap) {
		try {
			return type.cast(value, heap);
		}
		catch(...) {
			return value::null;
		}
	}
}