#include "instructions.hxx"
#include "ltnvm/LtnVM.hxx"
#include "ltnvm/stringify.hxx"

namespace ltn::vm::inst {
	void for_each(VmCore & core) {
		const auto addr = core.fetch_uint();
		const auto restore = core.pc;
		const auto container = core.stack.pop();
		if(is_array(container)) {
			const auto & array = core.heap.read<Array>(container.u);
			for(const auto & elem : array) {
				core.stack.push(elem);
				core.pc = core.code_begin + addr;
				const auto return_value = run_core(core);
				// std::cout << "ABC" << stringify(return_value, core.heap) << "\n";
			}
			core.pc = restore;
			return;
		}
	}
}