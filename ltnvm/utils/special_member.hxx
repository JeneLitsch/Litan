#pragma once
#include "ltn/reserved_members.hxx"
#include "ltnvm/VMCore.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/run_function.hxx"

namespace ltn::vm {
	Value run_core(VMCore & core);



	template<ReservedMemberCode CODE>
	std::optional<Value> find_special_member(const Struct & strukt) {
		for(const auto & [code, ref] : strukt.members) {
			if(static_cast<ReservedMemberCode>(code) == CODE) {
				return ref;
			}
		}
		return std::nullopt;
	}



	Value run_special_member(
		VMCore & core,
		const Value & ref,
		const Value & self,
		const auto & ...args) {
		return run_function(core, ref, self, args...);
	}


	
	template<ReservedMemberCode CODE>
	Value call_special_member(VMCore & core, const Value & self, const auto & ...args) {
		auto & strukt = *value::as<Struct>(self);
		if(auto ref = find_special_member<CODE>(strukt)) {
			return run_special_member(core, *ref, self, args...);
		}
		switch (CODE) {
			case ReservedMemberCode::OPERATOR_ADD: throw except::missing_operator("_+_");
			case ReservedMemberCode::OPERATOR_SUB: throw except::missing_operator("_-_");
			case ReservedMemberCode::OPERATOR_MLT: throw except::missing_operator("_*_");
			case ReservedMemberCode::OPERATOR_DIV: throw except::missing_operator("_/_");
			case ReservedMemberCode::OPERATOR_MOD: throw except::missing_operator("_%_");
			case ReservedMemberCode::OPERATOR_POW: throw except::missing_operator("_**_");
			default: throw except::missing_operator("");
		}
	}
}