#pragma once
#include "LtncType.hxx"
#include "LtncVarId.hxx"
#include <cstdint>
#include <string>
namespace ltn::c {
	struct Var {
		Var(const TypeId & typeId, std::uint32_t addr, const VarId & id)
			: typeId(typeId), addr(addr), name(id.name) {}
		
		TypeId typeId;
		std::uint32_t addr;
		std::string name;

		bool operator==(const Var & var) const {
			return this->name == var.name;
		}
	};

	inline bool operator==(const Var & var, const VarId & id) {
		return var.name == id.name;
	}
	inline bool operator==(const VarId & id, const Var & var) {
		return var.name == id.name;
	}

	struct Param {
		Param(const TypeId & typeId, const VarId & id)
			: typeId(typeId), name(id.name) {}
		TypeId typeId;
		std::string name;
	};
}