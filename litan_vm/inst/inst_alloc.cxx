#include "instructions.hxx"
#include "litan_vm/utils/type_check.hxx"
#include "litan_vm/utils/convert.hxx"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "litan_core/type_code.hxx"

namespace ltn::vm::inst {

	void pushAll(auto & array, VMStack & stack, std::uint64_t size) {
		if(!size) return;
		const auto value = stack.pop();
		pushAll(array, stack, size -1);
		array.push_back(value);
	} 



	void newarr(VMCore & core){
		core.heap.collect_garbage(core.stack);
		auto * arr = core.heap.make<Array>(); 
		const auto size = core.fetch_uint();
		pushAll(*arr, core.stack, size);
		core.stack.push(value::array(arr));
	}



	void newstr(VMCore & core) {
		core.heap.collect_garbage(core.stack);
		const std::uint64_t index = core.fetch_uint();
		const auto ptr = core.heap.alloc(String{String::non_owning, core.string_pool[index]});
		core.stack.push(value::string(ptr));
	}



	void newstruct(VMCore & core) {
		core.heap.collect_garbage(core.stack);
		const auto ptr = core.heap.alloc<Struct>({});
		core.stack.push(value::strukt(ptr));
	}



	void newmap(VMCore & core) {
		core.heap.collect_garbage(core.stack);
		const auto ref = core.heap.alloc<Map>(Map{&core});
		core.stack.push(value::map(ref));
	}



	void newfx(VMCore & core){
		core.heap.collect_garbage(core.stack);
		const auto index = core.fetch_uint();
		auto * entry = core.function_pool[index];
		ScriptFunctionPointer fx_ptr { index, entry->arity, entry->is_variadic };
		const auto ref = core.heap.alloc(std::move(fx_ptr));
		core.stack.push(value::fx(ref));
	}



	void newtuple(VMCore & core){
		core.heap.collect_garbage(core.stack);
		const auto size = core.fetch_uint();
		auto * tup = core.heap.alloc<Tuple>({});
		pushAll(*tup, core.stack, size);
		core.stack.push(value::tuple(tup));
	}
}