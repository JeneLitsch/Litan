#include "Tuple.hxx"
#include "litan_vm/Exception.hxx"
#include "litan_vm/utils/stringify.hxx"
#include "litan_vm/stdlib/tuple.hxx"

namespace ltn::vm {
	void Tuple::stringify(VMCore & core, std::ostream & oss, bool) {
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


	Value Tuple::get_member(VMCore & core, std::uint64_t id) const {
		return core.types.tuple.get_nonstatic_member(core, id);
	}
}