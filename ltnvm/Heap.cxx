#include "Heap.hxx"
#include <stdexcept>
#include <sstream>
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
		return addr + 1;
	}
	else {
		std::uint64_t addr = this->reuse.front();
		this->reuse.pop();
		this->objects[addr] = object;
		return addr + 1;
	}
}

std::uint64_t ltn::vm::Heap::allocString() {
	return this->alloc({String{}});
}

std::uint64_t ltn::vm::Heap::allocArray() {
	return this->alloc({Array{}});
}

ltn::vm::HeapObject & ltn::vm::Heap::get(std::uint64_t addr) {
	if(addr == 0) {
		throw accessViolation(addr, "nullptr");
	}
	if(addr > this->objects.size()) {
		throw accessViolation(addr, "");
	}
	return this->objects[addr-1];
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

