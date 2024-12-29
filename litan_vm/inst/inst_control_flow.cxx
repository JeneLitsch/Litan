#include "instructions.hxx"
#include "litan_vm/utils/type_check.hxx"
#include "litan_vm/utils/convert.hxx"
#include <sstream>
#include <stack>



namespace ltn::vm::inst {
	void jump(VMCore & core) {
		const auto address = core.fetch_uint(); 
		core.pc = core.code_begin + address;
	}



	void call(VMCore & core) {
		// std::cout << core.stack.depth() << "\n";
		const auto index = core.fetch_uint();
		const auto * entry = core.function_pool[index];
		const auto address = entry->address; 
		core.stack.push_frame(core.pc, entry->arity + entry->is_variadic, entry);
		core.pc = core.code_begin + address;
	}



	void reTurn(VMCore & core) {
		auto return_value = core.stack.pop();
		core.pc = core.stack.pop_frame();
		core.stack.push(return_value);
	}



	void iF(VMCore & core) {
		const auto value = core.stack.pop();
		const auto elseAddr = core.fetch_uint();
		if(!convert::to_bool(value, core)) {
			core.pc = core.code_begin + elseAddr;
		}
	}



	void error(VMCore &) {
		throw value::null;
	}



	void exit(VMCore & core) {
		throw core.stack.pop();
	}



	void for_next(VMCore & core) {
		const auto elseAddr = core.fetch_uint();
		const auto iter = core.stack.peek();
		const Value elem = iterator::next(iter); 
		if(is_iterator_stop(elem)) {
			core.stack.pop(); // Remove iterator
			core.pc = core.code_begin + elseAddr;
		}
		else {
			core.stack.push(elem);
		}
	}



	void return_null(VMCore & core) {
		core.pc = core.stack.pop_frame();
		core.stack.push(value::null);
	}



	void tail(VMCore & core) {
		const auto index = core.fetch_uint();
		const auto * context = core.function_pool[index];
		const std::int64_t total_arity = context->arity + context->is_variadic;
		core.stack.reuse_frame(total_arity, context);
		core.pc = core.code_begin + context->address;
	}
}