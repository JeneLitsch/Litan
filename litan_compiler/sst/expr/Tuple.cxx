#include "Tuple.hxx"

namespace ltn::c::sst::expr {
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



	void Tuple::push_back(expr_ptr elem) {
		this->elements.push_back(std::move(elem));
	}



	std::unique_ptr<Tuple> tuple() {
		return std::make_unique<Tuple>();
	}
}