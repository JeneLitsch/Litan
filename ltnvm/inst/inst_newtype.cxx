#include "instructions.hxx"
#include "ltnvm/type.hxx"

namespace ltn::vm::inst {
	void newtype(VmCore & core){
		const auto cstr = core.fetch_str();
		auto [node, end] = make_type(core, cstr);
		core.stack.push(value::type(node));
		core.pc = end + 1;
		core.heap.collect_garbage(core.stack, core.static_variables);
	}
}