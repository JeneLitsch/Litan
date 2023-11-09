#include "Array.hxx"

namespace ltn::c::sst::expr {
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


	
	void Array::push_back(expr_ptr elem) {
		this->elements.push_back(std::move(elem));
	}



	std::unique_ptr<Array> array() {
		return std::make_unique<Array>();
	}
}