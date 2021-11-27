#include "Heap.hxx"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include "ltnvm/TypeCheck.hxx"



ltn::vm::Heap::Heap() {}


ltn::vm::HeapObject & ltn::vm::Heap::get(std::uint64_t addr) {
	if(addr > this->objects.size()) {
		throw accessViolation(addr, "");
	}
	return this->objects[addr];
}

void ltn::vm::Heap::collectGarbage(const Stack & stack, const Register & reg) {
	mark(stack.getContainer());
	mark(reg.getContainer());
	sweep();
}

void ltn::vm::Heap::mark(const std::vector<Value> & values) {
	for(const auto & value : values) {
		if(isArr(value)) {
			auto & obj = get(value.u);
			auto & arr = read<Array>(value.u);
			obj.marked = true;
			mark(arr.arr);
		}
		if(isStr(value)
		|| isOStream(value)
		|| isIStream(value)
		|| isFxPtr(value)
		|| isClock(value)) {
			auto & obj = get(value.u);
			obj.marked = true;
		}
	}
}

void ltn::vm::Heap::sweep() {
	std::uint64_t idx = 0;
	for(auto & obj : this->objects) {
		if(obj.marked) {
			obj.marked = false;
		}
		else if(!std::get_if<std::monostate>(&obj.obj)) {
			obj.obj = std::monostate();
			this->reuse.push(idx);
		}
		idx++;
	}
}

void ltn::vm::Heap::reset() {
	this->objects.clear();
	this->reuse = {};
}
