#include "Tuple.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm {
	Value Tuple::at(std::int64_t index) const {
		if (index < 0) {
			throw except::out_of_range();
		}
		if (index >= std::ssize(*this)) {
			throw except::out_of_range();
		}
		return this->unsafe_at(index);
	}
}