#pragma once
#include "Segmented.hxx"

namespace ltn::vm {
	struct Stack : Segmented {
		virtual void stringify(VMCore & core, std::ostream & oss, bool nested) override;

		Stack() 
			: Segmented{} {};
	};

	inline Stack clone(const Stack & arr) {
		return arr;
	}
}