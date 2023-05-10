#include "Type.hxx"

namespace ltn::vm {
	std::string type_name(const Type & type) {
		return type.node->name();
	}



	bool type_is(const Type & type, const Value & value, Heap & heap) {
		return type.node->is(value, heap);
	}



	Value type_cast(const Type & type, const Value & value, Heap & heap) {
		try {
			return type.node->cast(value, heap);
		}
		catch(...) {
			return value::null;
		}
	}
}