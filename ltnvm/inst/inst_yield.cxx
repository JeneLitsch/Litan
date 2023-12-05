#include "instructions.hxx"

namespace ltn::vm::inst {
	void yield(VMCore & core) {
		core.heap.collect_garbage(core.stack);
		const auto coroutine = core.heap.make<Coroutine>();

		const auto return_value = core.stack.pop();
		coroutine->resume_address = core.pc;
		coroutine->local_variables = core.stack.copy_locals();
		core.pc = core.stack.pop_frame();
		
		const auto tuple = core.heap.make<Tuple>();
		
		tuple->push_back(value::coroutine(coroutine));
		tuple->push_back(return_value);

		core.stack.push(value::tuple(tuple));
	}




	void co_retvrn(VMCore & core) {
		core.heap.collect_garbage(core.stack);

		const auto return_value = core.stack.pop();
		core.pc = core.stack.pop_frame();
		
		const auto tuple = core.heap.make<Tuple>();
		
		tuple->push_back(value::noroutine);
		tuple->push_back(return_value);

		core.stack.push(value::tuple(tuple));
	}



	void co_dump(VMCore & core) {
		core.heap.collect_garbage(core.stack);
		const auto coroutine = core.heap.make<Coroutine>();

		coroutine->resume_address = core.pc;
		coroutine->local_variables = core.stack.copy_locals();
		core.pc = core.stack.pop_frame();
		
		core.stack.push(value::coroutine(coroutine));
	}
}