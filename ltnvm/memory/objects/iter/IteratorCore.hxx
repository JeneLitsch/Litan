#pragma once
#include "ltnvm/memory/Value.hxx"


namespace ltn::vm {
	struct VmCore;
	class Heap;
}

namespace ltn::vm::iter {
	class IteratorCore {
	public:
		virtual Value next(Heap &) = 0;
		virtual void mark(Heap &) = 0;
		virtual ~IteratorCore() = default; 
	};
}