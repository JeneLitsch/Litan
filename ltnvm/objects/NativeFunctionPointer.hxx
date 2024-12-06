#pragma once
#include "FunctionPointer.hxx"
#include "ltnvm/Value.hxx"

namespace ltn::vm {
	using NativeFunctionHandle = Value(*)(const Value *);

	struct NativeFunctionPointer : public FunctionPointer {
		NativeFunctionPointer(NativeFunctionHandle handle,  std::uint64_t parameter_count, bool is_variadic = false)
			: FunctionPointer { parameter_count, is_variadic }
			, handle{handle} {}

		NativeFunctionHandle handle;

		virtual ~NativeFunctionPointer() = default;
	};
}