#include "instructions.hxx"

namespace ltn::vm::inst {
	void newtype(VmCore & core){
		const auto code = core.fetch_str();
		auto [node, end] = core.type_table.make(code);
		core.stack.push(value::type(node));
		core.pc = end + 1;
		core.heap.collect_garbage(core.stack, core.static_variables);
	}
}