#include "NativeFunctionPointer.hxx"
#include "native/plugin.h"

namespace ltn::vm {
	bool NativeFunctionPointer::uses_gc() const {
		return (flags & ltn_USE_GC) > 0;
	}
}