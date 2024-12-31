#pragma once
#include "litan_vm/VMCore.hxx"

namespace ltn::vm {
	class GCLock final {
	public:
		GCLock(const NativeFunctionPointer * fx_ptr, VMCore * core);
		
		GCLock(const GCLock &) = delete;
		GCLock(GCLock &&) = delete;
		GCLock operator=(const GCLock &) = delete;
		GCLock operator=(GCLock &&) = delete;
		
		~GCLock();

	private:
		VMCore * core;
		const NativeFunctionPointer * fx_ptr;
	};
}