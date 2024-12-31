#include "GCLock.hxx"

namespace ltn::vm {
	GCLock::GCLock(const NativeFunctionPointer * fx_ptr, VMCore * core)
		: fx_ptr { fx_ptr } 
		, core { core } {
		if (!fx_ptr->uses_gc()) {
			core->heap.lock_gc();
		}
	}
	
	
	GCLock::~GCLock() {
		if (!fx_ptr->uses_gc()) {
			core->heap.unlock_gc();
		}
	}
}