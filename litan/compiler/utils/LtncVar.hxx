#pragma once
#include "LtncType.hxx"
#include <cstdint>
#include <string>
namespace ltnc {
	struct Var {
		Var(Type type, std::uint32_t  addr)
			: type(type), addr(addr) {}
		Type type;
		std::uint32_t addr;
	};

	struct Param {
		Param(Type type, const std::string & name)
			: type(type), name(name) {}
		Type type;
		std::string name;
	};
}