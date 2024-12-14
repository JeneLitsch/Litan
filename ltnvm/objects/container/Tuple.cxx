#include "Tuple.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/stringify.hxx"
#include "ltnvm/stdlib/tuple.hxx"

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


	Value Tuple::get_member(std::uint64_t id) const {
		static NativeFunctionTable native_function_table {
			wrap<stdlib::tuple_size>     (MemberCode::SIZE),
			wrap<stdlib::tuple_is_empty> (MemberCode::IS_EMTPY),
			wrap<stdlib::tuple_at>       (MemberCode::AT),
			wrap<stdlib::tuple_front>    (MemberCode::FRONT),
			wrap<stdlib::tuple_back>     (MemberCode::BACK),
		};
		return search_native_function_table(native_function_table, id);
	}
}