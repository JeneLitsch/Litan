#include "NativeFunctionPointer.hxx"
#include "litan_native/plugin.h"

namespace ltn::vm {
	bool NativeFunctionPointer::uses_gc() const {
		return (flags & ltn_USE_GC) > 0;
	}
}