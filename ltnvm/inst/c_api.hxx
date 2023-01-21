#pragma once
#include "ltnvm/external/Parameters.hxx"
#include "ltnvm/memory/Heap.hxx"

namespace ltn::vm {
	struct CoreWrapper {
		ext::Parameters params;
		Heap * heap;
		Value return_value = value::null;
	};

	CoreWrapper wrap_core(Heap & heap, const Array & args);

	CApi bind_api(CoreWrapper & wrapper);
}