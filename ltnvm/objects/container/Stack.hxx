#pragma once
#include "Segmented.hxx"

namespace ltn::vm {
	struct Stack : Segmented {
		Stack() 
			: Segmented{} {};
	};

	inline Stack clone(const Stack & arr) {
		return arr;
	}
}