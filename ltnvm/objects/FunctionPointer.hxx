#pragma once
#include "Object.hxx"

namespace ltn::vm {
	struct Core;
	struct FunctionPointer : Object {
		FunctionPointer(std::uint64_t parameter_count, bool is_variadic = false)
			: Object{}
			, params{ parameter_count }
			, is_variadic {is_variadic} {} 
		std::uint64_t params;
		std::uint64_t arity() const {
			return this->params;
		}
		bool is_variadic;

		std::vector<Value> captured;

		virtual ~FunctionPointer() = default;
	};
}