#include "algorithm.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/index.hxx"
#include "ltnvm/inst/instructions.hxx"
#include "ltnvm/utils/stringify.hxx"

namespace ltn::vm::build_in {
	template<auto INST>
	auto run_inst(VmCore & core) {
		INST(core);
		return core.stack.pop();
	}
	


	Value contains(VmCore & core) {
		return run_inst<inst::contains>(core);
	}
	
	Value size(VmCore & core) {
		return run_inst<inst::size>(core);
	}
	
	Value empty(VmCore & core) {
		return run_inst<inst::empty>(core);
	}
	
	Value at(VmCore & core) {
		return run_inst<inst::at>(core);
	}
	
	Value front(VmCore & core) {
		return run_inst<inst::front>(core);
	}
	
	Value back(VmCore & core) {
		return run_inst<inst::back>(core);
	}
}