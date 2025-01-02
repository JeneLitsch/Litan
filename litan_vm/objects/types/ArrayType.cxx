#include "ArrayType.hxx"
#include "litan_vm/stdlib/array.hxx"

namespace ltn::vm {
	static NativeFunctionTable nonstatic_functions {
		wrap<stdlib::array_size>     (ReservedMemberCode::SIZE),
		wrap<stdlib::array_is_empty> (ReservedMemberCode::IS_EMTPY),
		wrap<stdlib::array_push>     (ReservedMemberCode::PUSH),
		wrap<stdlib::array_pop>      (ReservedMemberCode::POP),
		wrap<stdlib::array_front>    (ReservedMemberCode::FRONT),
		wrap<stdlib::array_back>     (ReservedMemberCode::BACK),
		wrap<stdlib::array_peek>     (ReservedMemberCode::PEEK),
		wrap<stdlib::array_at>       (ReservedMemberCode::AT),
		wrap<stdlib::array_insert>   (ReservedMemberCode::INSERT),
		wrap<stdlib::array_erase>    (ReservedMemberCode::ERASE),
		wrap<stdlib::array_values>   (ReservedMemberCode::VALUES),
		wrap<stdlib::array_filter>   (ReservedMemberCode::FILTER),
		wrap<stdlib::array_transform>(ReservedMemberCode::TRANSFORM),
		wrap<stdlib::array_reduce>   (ReservedMemberCode::REDUCE),
		wrap<stdlib::array_any>      (ReservedMemberCode::ANY),
		wrap<stdlib::array_all>      (ReservedMemberCode::ALL),
		wrap<stdlib::array_none>     (ReservedMemberCode::NONE),
		wrap<stdlib::array_has>      (ReservedMemberCode::HAS),
		wrap<stdlib::array_slice>    (ReservedMemberCode::SLICE),
		wrap<stdlib::array_prefix>   (ReservedMemberCode::PREFIX),
		wrap<stdlib::array_suffix>   (ReservedMemberCode::SUFFIX),
		wrap<stdlib::array_reversed> (ReservedMemberCode::REVERSED),
		wrap<stdlib::array_zipped>   (ReservedMemberCode::ZIPPED),
	};


	static NativeFunctionTable static_functions {
		wrap<stdlib::array_new>      (ReservedMemberCode::NEW),
	};



	Value ArrayType::get_member(VMCore & core, std::uint64_t id) const {
		if(auto member = search_native_function_table(static_functions, id)) {
			return member.value();
		}
		return get_nonstatic_member(core, id);
	}



	Value ArrayType::get_nonstatic_member(VMCore & core, std::uint64_t id) const {
		return search_native_function_table(nonstatic_functions, id).value_or(value::null);
	}
}