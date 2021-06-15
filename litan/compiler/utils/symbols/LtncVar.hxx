#pragma once
#include "LtncType.hxx"
#include <cstdint>
#include <string>
namespace ltnc {
	struct Var {
		Var(const TypeId & typeId, std::uint32_t addr, const std::string & name)
			: typeId(typeId), addr(addr), name(name) {}
		TypeId typeId;
		std::uint32_t addr;
		std::string name;


		bool operator==(const Var & var) const {
			return this->name == var.name;
		}
	};

	inline bool operator==(const Var & var, const std::string & name) {
		return var.name == name;
	}
	inline bool operator==(const std::string & name, const Var & var) {
		return var.name == name;
	}

	struct Param {
		Param(const TypeId & typeId, const std::string & name)
			: typeId(typeId), name(name) {}
		TypeId typeId;
		std::string name;
	};
}