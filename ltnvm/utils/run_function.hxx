#pragma once
#include "ltn/MemberCode.hxx"
#include "ltnvm/VMCore.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm {
	Value run_core(VMCore & core);

	Value run_function(
		VMCore & core,
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
		for(const auto c : fx.captured) core.stack.push(c);
		auto result = run_core(core);
		core.pc = prev;
		return result;
	}
}