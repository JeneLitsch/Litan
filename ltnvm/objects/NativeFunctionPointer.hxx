#pragma once
#include "FunctionPointer.hxx"
#include "ltnvm/Value.hxx"

namespace ltn::vm {
	struct NativeCore {
		void * core;
		Value(*alloc_array)(NativeCore * native_core, const Value * data, uint64_t size);
		Value(*alloc_map)(NativeCore * native_core, const Value * key_data, const Value * value_data, uint64_t size);
	};
	using NativeFunctionHandle = Value(*)(NativeCore *, const Value *);


	struct NativeFunctionPointer : public FunctionPointer {
		NativeFunctionPointer(NativeFunctionHandle handle,  std::uint64_t parameter_count, bool is_variadic = false)
			: FunctionPointer { parameter_count, is_variadic }
			, handle{handle} {}

		NativeFunctionHandle handle;

		virtual ~NativeFunctionPointer() = default;
	};
}