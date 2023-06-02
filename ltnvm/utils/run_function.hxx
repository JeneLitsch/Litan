#pragma once
#include "ltn/MemberCode.hxx"
#include "ltnvm/VmCore.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm {
	Value run_core(VmCore & core);

	Value run_function(
		VmCore & core,
		const Value & ref,
		const auto & ...args) {
		const auto arity = sizeof...(args);
		auto & fx = core.heap.read<FxPointer>(ref);
		if(fx.params != arity) throw except::invalid_parameters(arity, fx.params);
		if(fx.is_variadic) throw except::invalid_member_access();
		(core.stack.push(args),...);
		const auto prev = core.pc;
		core.pc = fx.ptr;
		core.stack.push_frame(core.code_end - 1, arity);
		auto result = run_core(core);
		core.pc = prev;
		return result;
	}
}