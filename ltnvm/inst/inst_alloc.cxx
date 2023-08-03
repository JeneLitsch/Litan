#include "instructions.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/utils/convert.hxx"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "ltn/type_code.hxx"

namespace ltn::vm::inst {

	void pushAll(auto & array, Stack & stack, std::uint64_t size) {
		if(!size) return;
		const auto value = stack.pop();
		pushAll(array, stack, size -1);
		array.push_back(value);
	} 



	void newarr(VmCore & core){
		const auto ptr = value::array(core.heap.alloc<Array>({}));
		auto & arr = core.heap.read<Array>(ptr); 
		const auto size = core.fetch_uint();
		pushAll(arr, core.stack, size);
		core.stack.push(ptr);
		core.heap.collect_garbage(core.stack);
	}



	void newstr(VmCore & core) {
		const auto size = core.fetch_uint();
		const auto cstr = core.fetch_str();
		std::string str(cstr, cstr + size); 
		const auto ptr = core.heap.alloc<String>({std::move(str)});
		core.stack.push({ ptr, Value::Type::STRING });
		core.pc += size;
		core.heap.collect_garbage(core.stack);
	}



	void newclock(VmCore & core) {
		const auto ptr = core.heap.alloc<Clock>({});
		core.stack.push({ ptr, Value::Type::CLOCK });
		core.heap.collect_garbage(core.stack);
	}



	void newstruct(VmCore & core) {
		const auto ptr = core.heap.alloc<Struct>({});
		core.stack.push({ ptr, Value::Type::STRUCT });
		core.heap.collect_garbage(core.stack);
	}



	void newstack(VmCore & core) {
		const auto ref = core.heap.alloc<Deque>({});
		core.stack.push({ ref, Value::Type::STACK });
		core.heap.collect_garbage(core.stack);
	}



	void newqueue(VmCore & core) {
		const auto ref = core.heap.alloc<Deque>({});
		core.stack.push({ ref, Value::Type::QUEUE });
		core.heap.collect_garbage(core.stack);
	}



	void newmap(VmCore & core) {
		const auto ref = core.heap.alloc<Map>(Map{&core});
		core.stack.push({ ref, Value::Type::MAP });
		core.heap.collect_garbage(core.stack);
	}



	void newfx(VmCore & core){
		const auto address = core.code_begin + core.fetch_uint(); 
		const auto arity_code = core.fetch_uint();
		const auto arity = (arity_code << 1) >> 1;
		const auto is_variadic = (arity_code >> 63) != 0;
		FxPointer fx_ptr { address, arity, {}, is_variadic };
		const auto ref = core.heap.alloc(std::move(fx_ptr));
		core.stack.push(Value{ref, Value::Type::FUNCTION});
	}



	void newtuple(VmCore & core){
		const auto ptr = value::tuple(core.heap.alloc<Array>({}));
		auto & arr = core.heap.read<Array>(ptr); 
		const auto size = core.fetch_uint();
		pushAll(arr, core.stack, size);
		core.stack.push(ptr);
		core.heap.collect_garbage(core.stack);
	}
}