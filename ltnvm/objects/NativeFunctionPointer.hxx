#pragma once
#include "FunctionPointer.hxx"
#include "ltnvm/Value.hxx"
#include "ltnvm/native/NativeCore.hxx"

namespace ltn::vm {
	struct Plugin;
	struct NativeFunctionPointer : public FunctionPointer {
		NativeFunctionPointer(Plugin * plugin, NativeFunctionHandle handle,  std::uint64_t parameter_count, bool is_variadic = false)
			: FunctionPointer { parameter_count, is_variadic }
			, handle{handle}
			, plugin{plugin} {}

		NativeFunctionHandle handle;

		virtual ~NativeFunctionPointer() = default;

		Plugin * plugin;
	};
}