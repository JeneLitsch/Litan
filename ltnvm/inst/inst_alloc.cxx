#include "instructions.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/utils/convert.hxx"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "ltn/type_code.hxx"

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
		const auto size = core.fetch_uint();
		const auto cstr = core.fetch_str();
		std::string str(cstr, cstr + size); 
		const auto ptr = core.heap.make<String>(std::move(str));
		core.stack.push(value::string(ptr));
		core.pc += size;
	}



	void newclock(VMCore & core) {
		core.heap.collect_garbage(core.stack);
		const auto ptr = core.heap.make<Clock>();
		core.stack.push(value::clock(ptr));
	}



	void newstruct(VMCore & core) {
		core.heap.collect_garbage(core.stack);
		const auto ptr = core.heap.alloc<Struct>({});
		core.stack.push(value::strukt(ptr));
	}



	void newstack(VMCore & core) {
		core.heap.collect_garbage(core.stack);
		core.stack.push(value::stack(core.heap.make<Stack>()));
	}



	void newqueue(VMCore & core) {
		core.heap.collect_garbage(core.stack);
		core.stack.push(value::queue(core.heap.make<Queue>()));
	}



	void newmap(VMCore & core) {
		core.heap.collect_garbage(core.stack);
		const auto ref = core.heap.alloc<Map>(Map{&core});
		core.stack.push(value::map(ref));
	}



	void newfx(VMCore & core){
		core.heap.collect_garbage(core.stack);
		const auto index = core.fetch_uint(); 
		const auto arity_code = core.fetch_byte();
		const auto arity = arity_code & 0b01111111;
		const auto is_variadic = static_cast<bool>(arity_code & 0b10000000);
		FxPointer fx_ptr { index, static_cast<std::uint8_t>(arity), {}, is_variadic };
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