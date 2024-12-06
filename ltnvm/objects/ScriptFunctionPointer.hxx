#pragma once
#include <cstdint>
#include <string_view>
#include <vector>
#include "ltnvm/Value.hxx"
#include "ltnvm/objects/Object.hxx"
//#include "ScriptFunctionPointer.hxx"

namespace ltn::vm {
	struct ScriptFunctionPointer : public Object {
		ScriptFunctionPointer(std::uint64_t index, std::uint64_t params, std::vector<Value> captured, bool is_variadic = false)
			: Object{}
			, index{index} 
			, params{params}
			, captured{std::move(captured)}
			, is_variadic{is_variadic} {}

		std::uint64_t index;
		std::uint64_t params;
		std::uint64_t arity() const {
			return this->params;
		}
		std::vector<Value> captured;
		bool is_variadic = false;
		constexpr static std::string_view typeName = "ScriptFunctionPointer";
	};



	inline ScriptFunctionPointer clone(const ScriptFunctionPointer & fx_ptr) {
		return fx_ptr;
	}
}