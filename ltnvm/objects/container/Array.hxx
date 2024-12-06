#pragma once
#include "Contiguous.hxx"

namespace ltn::vm {
	struct Array : Contiguous {
		Array() 
			: Contiguous{} {};

		Array(std::vector<Value> && values) 
			: Contiguous{std::move(values)} {};

		virtual Value get_member(std::uint64_t id) const override;
	};

	inline Array clone(const Array & arr) {
		return arr;
	}
}