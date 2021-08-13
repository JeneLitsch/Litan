#pragma once
#include <optional>
#include <vector>
#include <string>
#include <memory>
#include <set>

#include "LtncTypeId.hxx"

namespace ltn::c {
	struct Var;
	struct Type {

		Type() : Type(TypeId("voi"), {}) {}
		Type(const TypeId & id, const std::vector<TypeId> & castableTo = {}) 
			: id(id), castableTo(castableTo) { this->castableTo.push_back(id); }

		TypeId id;
		std::vector<std::shared_ptr<Var>> members;
		unsigned fixedSize = 0;
		std::vector<TypeId> castableTo;

		bool isCastableTo(const TypeId & id) const {
			for(const TypeId & castable : this->castableTo) {
				if(castable == id) {
					return true;
				}
			}
			return false;
		}
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