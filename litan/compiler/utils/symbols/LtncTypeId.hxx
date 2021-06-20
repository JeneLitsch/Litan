#pragma once
#include <string>
namespace ltnc {
	struct TypeId {
		TypeId(const std::string & name)
			: name(name) {}

		std::string name;
	};

	inline bool operator==(const TypeId & l, const TypeId & r) {
		return l.name == r.name;
	}
}