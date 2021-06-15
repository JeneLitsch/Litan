#pragma once
#include <string>
namespace ltnc {
	struct TypeId {
		TypeId(const std::string & name)
			: name(name) {}

		TypeId(const TypeId & typeId)
			: name(typeId.name) {}
	
		std::string name;
	};

	inline bool operator==(const TypeId & l, const TypeId & r) {
		return l.name == r.name;
	}
}