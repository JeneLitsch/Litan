#pragma once
#include "FunctionPointer.hxx"
#include "litan_vm/Value.hxx"
#include "litan_vm/native/NativeCore.hxx"

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
		std::uint64_t flags;

		bool uses_gc() const;
	};
}