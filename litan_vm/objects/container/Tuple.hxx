#pragma once
#include <vector>
#include <string_view>
#include "litan_vm/Value.hxx"
#include "litan_vm/objects/Object.hxx"
#include "Contiguous.hxx"

namespace ltn::vm {
	struct Tuple : Contiguous {
		Tuple() 
			: Contiguous{} {};

		Tuple(std::vector<Value> && values) 
			: Contiguous{std::move(values)} {};

		virtual Value get_member(VMCore & core, std::uint64_t id) const override;
		virtual void stringify(VMCore & core, std::ostream & oss, bool nested) override;

		Value at(std::int64_t index) const;
	};

	inline Tuple clone(const Tuple & tup) {
		return tup;
	}

}