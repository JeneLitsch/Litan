#include "instructions.hxx"

namespace ltn::vm::inst {
	void newtype(VMCore & core){
		const auto code = core.fetch_str();
		auto [node, end] = core.type_table.make(code);
		core.stack.push(value::type(core.type_table[node]));
		core.pc = end + 1;
	}
}