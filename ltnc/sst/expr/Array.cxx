#include "Array.hxx"

namespace ltn::c::sst {
	Array::Array() : Literal() {}



	std::uint64_t Array::alloc() const {
		std::uint64_t count = 0;
		for(const auto & elem : this->elements) {
			count = std::max(elem->alloc(), count);
		}
		return count;
	}



	void Array::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}
}