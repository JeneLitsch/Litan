#pragma once
#include "Contiguous.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm {
	struct Array : Contiguous {
		Array() 
			: Contiguous{} {};

		Array(std::vector<Value> && values) 
			: Contiguous{std::move(values)} {};

		virtual Value get_member(std::uint64_t id) const override;

		Value erase(std::int64_t i);
		void insert(std::int64_t i, Value value);

		const Value & at(std::int64_t i) const;
		Value & at(std::int64_t i);
		Value pop_back();

		const Value & front() const; 
		const Value & back() const; 
	};



	inline Array clone(const Array & arr) {
		return arr;
	}
}