#include "Tuple.hxx"

namespace ltn::c::sst {
	Tuple::Tuple() : Literal() {}



	std::uint64_t Tuple::alloc() const {
		std::uint64_t count = 0;
		for(const auto & elem : this->elements) {
			count = std::max(elem->alloc(), count);
		}
		return count;
	}



	void Tuple::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}
}