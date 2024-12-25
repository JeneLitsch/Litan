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


	Value Tuple::get_member(std::uint64_t id) const {
		static NativeFunctionTable native_function_table {
			wrap<stdlib::tuple_size>     (ReservedMemberCode::SIZE),
			wrap<stdlib::tuple_is_empty> (ReservedMemberCode::IS_EMTPY),
			wrap<stdlib::tuple_at>       (ReservedMemberCode::AT),
			wrap<stdlib::tuple_front>    (ReservedMemberCode::FRONT),
			wrap<stdlib::tuple_back>     (ReservedMemberCode::BACK),
			wrap<stdlib::tuple_values>   (ReservedMemberCode::VALUES),
		};
		return search_native_function_table(native_function_table, id);
	}
}