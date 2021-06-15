#pragma once
#include <optional>
#include <vector>
#include <string>
#include <memory>

#include "LtncTypeId.hxx"

namespace ltnc {
	struct Var;
	struct Type {

		Type(const TypeId & id) : id(id) {}
		Type() : id(TypeId("voi")) {}

		TypeId id;
		std::vector<std::shared_ptr<Var>> members;
		unsigned fixedSize = 0;
	};

	inline bool operator==(const Type & typeL, const Type & typeR) {
		return typeL.id == typeR.id;
	}

	inline bool operator==(const Type & type, const TypeId & typeId) {
		return type.id == typeId;
	}

	inline bool operator==(const TypeId & typeId, const Type & type) {
		return type.id == typeId;
	}
}