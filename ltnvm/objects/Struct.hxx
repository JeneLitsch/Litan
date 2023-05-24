#pragma once
#include <vector>
#include <utility>
#include "ltnvm/memory/Value.hxx"
#include "ltn/OperatorCode.hxx"

namespace ltn::vm {




	struct Struct {
		using Members = std::vector<std::pair<std::uint64_t, Value>>;
		using Operators = std::vector<std::pair<OperatorCode, Value>>;

		constexpr static std::string_view typeName = "Struct";
		
		Members members;
		Operators operators;
	};
	


	inline Struct clone(const Struct & strukt) {
		return strukt;
	}
}