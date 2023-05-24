#pragma once
#include "ltn/MemberCode.hxx"
#include "ltnvm/VmCore.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm {
	template<MemberCode CODE>
	void call_special_member(
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
				core.stack.push_frame(core.pc, arity);
				core.pc = fx.ptr;
				return;
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