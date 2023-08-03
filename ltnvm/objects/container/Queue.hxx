#pragma once
#include "Segmented.hxx"

namespace ltn::vm {
	struct Queue : Segmented {
		Queue() 
			: Segmented{} {};
	};

	inline Queue clone(const Queue & arr) {
		return arr;
	}
}