#pragma once
#include "Segmented.hxx"

namespace ltn::vm {
	struct Stack : Segmented {
		Stack() 
			: Segmented{} {};
			
		virtual void stringify(VMCore & core, std::ostream & oss, bool nested) override;
		virtual Value get_member(std::uint64_t id) const override;
	};

	inline Stack clone(const Stack & arr) {
		return arr;
	}
}