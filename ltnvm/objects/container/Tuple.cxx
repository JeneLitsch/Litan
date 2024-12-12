#include "Tuple.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/stringify.hxx"

namespace ltn::vm {
	void Tuple::stringify(VMCore & core, std::ostream & oss, bool nested) {
		print_all(std::begin(data), std::end(data), oss, core, '(', ')');
	}


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