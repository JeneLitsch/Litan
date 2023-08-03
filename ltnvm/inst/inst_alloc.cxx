#include "instructions.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/utils/convert.hxx"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "ltn/type_code.hxx"

namespace ltn::vm::inst {

	void pushAll(auto & array, VmStack & stack, std::uint64_t size) {
		if(!size) return;
		const auto value = stack.pop();
		pushAll(array, stack, size -1);
		array.push_back(value);
	} 



	void newarr(VmCore & core){
		core.heap.collect_garbage(core.stack);
		auto * arr = core.heap.make<Array>(); 
		const auto size = core.fetch_uint();
		pushAll(*arr, core.stack, size);
		core.stack.push(value::array(arr));
	}



	void newstr(VmCore & core) {
		core.heap.collect_garbage(core.stack);
		const auto size = core.fetch_uint();
		const auto cstr = core.fetch_str();
		std::string str(cstr, cstr + size); 
		const auto ptr = core.heap.make<String>(std::move(str));
		core.stack.push(value::string(ptr));
		core.pc += size;
	}



	void newclock(VmCore & core) {
		core.heap.collect_garbage(core.stack);
		const auto ptr = core.heap.make<Clock>();
		core.stack.push({ ptr, Value::Type::CLOCK });
	}



	void newstruct(VmCore & core) {
		core.heap.collect_garbage(core.stack);
		const auto ptr = core.heap.alloc<Struct>({});
		core.stack.push({ ptr, Value::Type::STRUCT });
	}



	void newstack(VmCore & core) {
		core.heap.collect_garbage(core.stack);
		core.stack.push(value::stack(core.heap.make<Stack>()));
	}



	void newqueue(VmCore & core) {
		core.heap.collect_garbage(core.stack);
		core.stack.push(value::queue(core.heap.make<Queue>()));
	}



	void newmap(VmCore & core) {
		core.heap.collect_garbage(core.stack);
		const auto ref = core.heap.alloc<Map>(Map{&core});
		core.stack.push({ ref, Value::Type::MAP });
	}



	void newfx(VmCore & core){
		core.heap.collect_garbage(core.stack);
		const auto address = core.code_begin + core.fetch_uint(); 
		const auto arity_code = core.fetch_uint();
		const auto arity = (arity_code << 1) >> 1;
		const auto is_variadic = (arity_code >> 63) != 0;
		FxPointer fx_ptr { address, arity, {}, is_variadic };
		const auto ref = core.heap.alloc(std::move(fx_ptr));
		core.stack.push(value::fx(ref));
	}



	void newtuple(VmCore & core){
		core.heap.collect_garbage(core.stack);
		const auto size = core.fetch_uint();
		auto * tup = core.heap.alloc<Tuple>({});
		pushAll(*tup, core.stack, size);
		core.stack.push(value::tuple(tup));
	}
}