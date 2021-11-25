#include "Heap.hxx"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include "TypeCheck.hxx"

namespace {
	auto accessViolation(std::uint64_t at, const std::string_view msg) {
		std::stringstream ss;
		ss << "Access Violation at " << at << ": " << msg;
		return std::runtime_error{ ss.str() };
 	}
}

ltn::vm::Heap::Heap() {}

std::uint64_t ltn::vm::Heap::alloc(const HeapObject & object) {
	if(reuse.empty()) {
		const std::uint64_t addr = this->objects.size();
		this->objects.push_back(object);
		return addr;
	}
	else {
		std::uint64_t addr = this->reuse.front();
		this->reuse.pop();
		this->objects[addr] = object;
		return addr;
	}
}

std::uint64_t ltn::vm::Heap::allocString(const std::string & str) {
	return this->alloc({str});
}

std::uint64_t ltn::vm::Heap::allocArray(const Array & arr) {
	return this->alloc({arr});
}

ltn::vm::HeapObject & ltn::vm::Heap::get(std::uint64_t addr) {
	if(addr > this->objects.size()) {
		throw accessViolation(addr, "");
	}
	return this->objects[addr];
}

ltn::vm::String & ltn::vm::Heap::readString(std::uint64_t addr) {
	auto & object = get(addr);
	if(auto * string = std::get_if<String>(&object.obj)) {
		return *string;
	}
	else {
		throw accessViolation(addr, "not a string");
	}
}

ltn::vm::Array & ltn::vm::Heap::readArray(std::uint64_t addr) {
	auto & object = get(addr);
	if(auto * array = std::get_if<Array>(&object.obj)) {
		return *array;
	}
	else {
		throw accessViolation(addr, "not an array");
	}
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
			auto & arr = readArray(value.u);
			obj.marked = true;
			mark(arr);
		}
		if(isStr(value)) {
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
			std::cout << "Deleted: " << idx << "\n";
			this->reuse.push(idx);
		}
		idx++;
	}
}