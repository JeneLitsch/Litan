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
		this->objects[addr] = std::move(object);
		return addr;
	}
}

std::uint64_t ltn::vm::Heap::allocString(const std::string & str) {
	return this->alloc({str});
}

std::uint64_t ltn::vm::Heap::allocArray(const Array & arr) {
	return this->alloc({arr});
}

std::uint64_t ltn::vm::Heap::allocOStream(const OStream & out) {
	return this->alloc({out});
}

std::uint64_t ltn::vm::Heap::allocIStream(const IStream & in) {
	return this->alloc({in});
}

std::uint64_t ltn::vm::Heap::allocFxPointer(FxPointer fxPtr) {
	return this->alloc({fxPtr});
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

ltn::vm::OStream & ltn::vm::Heap::readOStream(std::uint64_t addr) {
	auto & object = get(addr);
	if(auto * stream = std::get_if<OStream>(&object.obj)) {
		return *stream;
	}
	else {
		throw accessViolation(addr, "not an ostream");
	}
}

ltn::vm::IStream & ltn::vm::Heap::readIStream(std::uint64_t addr) {
	auto & object = get(addr);
	if(auto * stream = std::get_if<IStream>(&object.obj)) {
		return *stream;
	}
	else {
		throw accessViolation(addr, "not an istream");
	}
}


ltn::vm::FxPointer & ltn::vm::Heap::readFxPointer(std::uint64_t addr) {
	auto & object = get(addr);
	if(auto * stream = std::get_if<FxPointer>(&object.obj)) {
		return *stream;
	}
	else {
		throw accessViolation(addr, "not an FxPointer");
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
		if(isStr(value)
		|| isOStream(value)
		|| isIStream(value)
		|| isFxPtr(value)) {
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