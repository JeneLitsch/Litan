#pragma once
#include "ltn/MemberCode.hxx"
#include "ltnvm/VmCore.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm {
	Value run_core(VmCore & core);
	
	template<MemberCode CODE>
	Value call_special_member(
		VmCore & core,
		const Value & self,
		const auto & ...args) {
		auto & strukt = core.heap.read<Struct>(self);
		const auto arity = 1 + sizeof...(args);
		for(const auto & [code, ref] : strukt.members) {
			if(static_cast<MemberCode>(code) == CODE) {
				auto & fx = core.heap.read<FxPointer>(ref);
				if(fx.params != arity) throw except::invalid_parameters(arity, fx.params);
				if(fx.is_variadic) throw except::invalid_member_access();
				core.stack.push(self);
				(core.stack.push(args),...);
				const auto prev = core.pc;
				core.pc = fx.ptr;
				core.stack.push_frame(core.code_end - 1, arity);
				auto result = run_core(core);
				core.pc = prev;
				return result;
			}
		}
		switch (CODE) {
			case MemberCode::ADD: throw except::missing_operator("_+_");
			case MemberCode::SUB: throw except::missing_operator("_-_");
			case MemberCode::MLT: throw except::missing_operator("_*_");
			case MemberCode::DIV: throw except::missing_operator("_/_");
			case MemberCode::MOD: throw except::missing_operator("_%_");
			case MemberCode::POW: throw except::missing_operator("_**_");
			default: throw except::missing_operator("");
		}
	}
}