#include "LtnvmHeap.hxx"


ltn::vm::Heap::Heap() {
	this->nextID = 1;
	this->objects.clear();
}

void ltn::vm::Heap::clear() {
	this->nextID = 1;
	this->objects.clear();
	this->resuseableIDs = {};
}


std::uint64_t ltn::vm::Heap::allocate(HeapType type)  {
	std::uint64_t newPtr = this->createPtr();
	this->objects.insert({newPtr, HeapObject(type)});
	return newPtr;
}

std::uint64_t ltn::vm::Heap::allocate(std::size_t size)  {
	std::uint64_t newPtr = this->createPtr();
	this->objects.insert({newPtr, HeapObject(size)});
	return newPtr;
}

std::uint64_t ltn::vm::Heap::copy(std::uint64_t ptr) {
	std::uint64_t newPtr = this->createPtr();
	this->objects.insert({newPtr, this->objects.at(ptr)});
	return newPtr;
}

std::uint64_t ltn::vm::Heap::createPtr() {
	std::uint64_t ptr;

	// determine id
	// new id
	if(this->resuseableIDs.empty()){
		ptr = this->nextID;
		this->nextID++;
	}
	// reuse id
	else{
		ptr = this->resuseableIDs.front();
		this->resuseableIDs.pop();
	}
	return ptr;
}

void ltn::vm::Heap::destroy(std::uint64_t ptr) {
	if(this->objects.contains(ptr)){
		this->resuseableIDs.push(ptr);
		this->objects.erase(ptr);
	}
	else{
		throw PointerAccessViolation(ptr, "Pointer");
	}
}

bool ltn::vm::Heap::exists(std::uint64_t ptr) const {
	return this->objects.contains(ptr);
}