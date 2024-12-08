#pragma once
#include "FunctionPointer.hxx"
#include "ltnvm/Value.hxx"
#include "ltnvm/native/NativeCore.hxx"

namespace ltn::vm {

	struct NativeFunctionPointer : public FunctionPointer {
		NativeFunctionPointer(NativeFunctionHandle handle,  std::uint64_t parameter_count, bool is_variadic = false)
			: FunctionPointer { parameter_count, is_variadic }
			, handle{handle} {}

		NativeFunctionHandle handle;

		virtual ~NativeFunctionPointer() = default;
	};
}