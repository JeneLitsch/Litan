#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include "ltnvm/convert.hxx"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace ltn::vm::inst {

	void pushAll(auto & array, Stack & stack, std::uint64_t size) {
		if(!size) return;
		const auto value = stack.pop();
		pushAll(array, stack, size -1);
		array.push_back(value);
	} 



	void newarr(VmCore & core){
		const auto arr = core.heap.alloc(Array{});
		const auto size = core.fetch_uint();
		// std::cout << "SIZE: " << size << "\n"; 
		pushAll(arr->arr, core.stack, size);
		core.stack.push(value::array(arr));
		core.heap.collect_garbage(core.stack, core.static_variables);
	}



	void newstr(VmCore & core) {
		const auto size = core.fetch_uint();
		const auto cstr = core.fetch_str();
		std::string str(cstr, cstr + size); 
		const auto ptr = core.heap.alloc(String{std::move(str)});
		core.stack.push(value::string(ptr));
		core.pc += size;
		core.heap.collect_garbage(core.stack, core.static_variables);
	}



	void newclock(VmCore & core) {
		const auto ptr = core.heap.alloc(Clock{});
		core.stack.push({ ptr, Value::Type::CLOCK });
		core.heap.collect_garbage(core.stack, core.static_variables);
	}



	void newstruct(VmCore & core) {
		const auto ptr = core.heap.alloc(Struct{});
		core.stack.push({ ptr, Value::Type::STRUCT });
		core.heap.collect_garbage(core.stack, core.static_variables);
	}



	void newstack(VmCore & core) {
		const auto ref = core.heap.alloc(Deque{});
		core.stack.push({ ref, Value::Type::STACK });
		core.heap.collect_garbage(core.stack, core.static_variables);
	}



	void newqueue(VmCore & core) {
		const auto ref = core.heap.alloc(Deque{});
		core.stack.push({ ref, Value::Type::QUEUE });
		core.heap.collect_garbage(core.stack, core.static_variables);
	}



	void newmap(VmCore & core) {
		const auto ref = core.heap.alloc(Map{Map::Data{Comparator{&core.heap}}});
		core.stack.push({ ref, Value::Type::MAP });
		core.heap.collect_garbage(core.stack, core.static_variables);
	}



	void newfx(VmCore & core){
		const auto address = core.code_begin + core.fetch_uint(); 
		const auto arity = core.fetch_uint();
		const auto ref = core.heap.alloc(FxPointer{address, arity, {}});
		core.stack.push(Value{ref, Value::Type::FX_PTR});
	}



	void newtuple(VmCore & core){
		const auto arr = core.heap.alloc(Array{});
		const auto size = core.fetch_uint();
		pushAll(arr->arr, core.stack, size);
		core.stack.push(value::tuple(arr));
		core.heap.collect_garbage(core.stack, core.static_variables);
	}
}