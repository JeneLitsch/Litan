#pragma once
#include <cstdint>
#include <string_view>
#include <vector>
#include "ltnvm/Value.hxx"
#include "ltnvm/objects/Object.hxx"
#include "FunctionPointer.hxx"

namespace ltn::vm {
	struct ScriptFunctionPointer : public FunctionPointer {
		ScriptFunctionPointer(std::uint64_t index, std::uint64_t params, bool is_variadic = false)
			: FunctionPointer{params}
			, index{index} 
			, is_variadic{is_variadic} {}

		std::uint64_t index;

		std::vector<Value> captured;
		bool is_variadic = false;
		constexpr static std::string_view typeName = "ScriptFunctionPointer";
	};



	inline ScriptFunctionPointer clone(const ScriptFunctionPointer & fx_ptr) {
		return fx_ptr;
	}
}