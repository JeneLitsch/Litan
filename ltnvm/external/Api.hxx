#pragma once
#include <vector>
#include "ltnvm/memory/Value.hxx"
#include "ltnvm/memory/Heap.hxx"
namespace ltn::vm::ext {
	class Api {
	public:
		Api(Heap & heap);
	private:
		Heap & heap;
	};
}