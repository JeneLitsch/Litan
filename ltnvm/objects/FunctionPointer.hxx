#pragma once
#include "Object.hxx"

namespace ltn::vm {
	struct FunctionPointer : Object {
		FunctionPointer(std::uint64_t parameter_count)
			: Object{}
			, params{ parameter_count } {} 
		std::uint64_t params;
		std::uint64_t arity() const {
			return this->params;
		}
	};
}