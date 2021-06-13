#pragma once
#include "LtncType.hxx"
#include <cstdint>
#include <string>
namespace ltnc {
	struct Var {
		Var(const std::string & typeName, std::uint32_t addr, const std::string & name)
			: typeName(typeName), addr(addr), name(name) {}
		std::string typeName;
		std::uint32_t addr;
		std::string name;


		bool operator==(const Var & var) const {
			return this->name == var.name;
		}
		bool operator<(const Var & var) const {
			return this->name < var.name;
		}
		bool operator>(const Var & var) const {
			return this->name > var.name;
		}
	};

	inline bool operator==(const Var & var, const std::string & name) {
		return var.name == name;
	}
	inline bool operator<(const Var & var, const std::string & name) {
		return var.name < name;
	}
	inline bool operator>(const Var & var, const std::string & name) {
		return var.name > name;
	}

	inline bool operator==(const std::string & name, const Var & var) {
		return var.name == name;
	}
	inline bool operator<(const std::string & name, const Var & var) {
		return var.name > name;
	}
	inline bool operator>(const std::string & name, const Var & var) {
		return var.name < name;
	}

	struct Param {
		Param(Type type, const std::string & name)
			: type(type), name(name) {}
		Type type;
		std::string name;
	};
}