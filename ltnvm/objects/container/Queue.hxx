#pragma once
#include "Segmented.hxx"

namespace ltn::vm {
	struct Queue : Segmented {
		Queue() 
			: Segmented{} {};

		virtual void stringify(VMCore & core, std::ostream & oss, bool nested) override;
		virtual Value get_member(std::uint64_t id) const override;
	};

	inline Queue clone(const Queue & arr) {
		return arr;
	}
}