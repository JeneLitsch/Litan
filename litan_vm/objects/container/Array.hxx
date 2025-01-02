#pragma once
#include "Contiguous.hxx"
#include "litan_vm/Exception.hxx"

namespace ltn::vm {
	struct Array : Contiguous {
		Array() 
			: Contiguous{} {};

		Array(std::vector<Value> && values) 
			: Contiguous{std::move(values)} {};

		Array(const std::vector<Value> & values) 
			: Contiguous{values} {};

		virtual Value get_member(VMCore & core, std::uint64_t id) const override;
		virtual void stringify(VMCore & core, std::ostream & oss, bool nested) override;


		Value erase(std::int64_t i);
		void insert(std::int64_t i, Value value);

		const Value & at(std::int64_t i) const;
		Value & at(std::int64_t i);
		Value pop_back();

		const Value & front() const; 
		const Value & back() const;

		Array reversed() const;
		Array slice(std::int64_t begin, std::int64_t end) const;
	};



	inline Array clone(const Array & arr) {
		return arr;
	}
}