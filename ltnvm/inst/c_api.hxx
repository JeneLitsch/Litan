#pragma once
#include "ltnvm/external/Parameters.hxx"
#include "ltnvm/memory/Heap.hxx"

namespace ltn::vm {
	struct CoreWrapper {
		ext::Parameters params;
		Heap * heap;
		Value return_value = value::null;
		Value library = value::null;
	};

	CoreWrapper wrap_core(Heap & heap, const Array & args, Value library);

	ltn_CApi bind_api(CoreWrapper & wrapper);
}