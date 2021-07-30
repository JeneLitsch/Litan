#include "LtnHeap.hxx"
#include "LtnNullptrViolation.hxx"
#include "LtnPointerAccessViolation.hxx"

ltn::Heap::Heap() {
	this->nextID = 1;
	this->objects.clear();
}

void ltn::Heap::clear() {
	this->nextID = 1;
	this->objects.clear();
	this->resuseableIDs = {};
}

std::uint64_t ltn::Heap::allocateArray()  {
	std::uint64_t newPtr = this->createPtr();
	this->objects.insert({newPtr, HeapObject(HeapObject::Type::ARRAY)});
	return newPtr;
}

std::uint64_t ltn::Heap::allocateString()  {
	std::uint64_t newPtr = this->createPtr();
	this->objects.insert({newPtr, HeapObject(HeapObject::Type::STRING)});
	return newPtr;
}

std::uint64_t ltn::Heap::copy(std::uint64_t ptr) {
	std::uint64_t newPtr = this->createPtr();
	this->objects.insert({newPtr, this->objects.at(ptr)});
	return newPtr;
}

std::uint64_t ltn::Heap::createPtr() {
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

void ltn::Heap::destroy(std::uint64_t ptr) {
	if(this->objects.contains(ptr)){
		this->resuseableIDs.push(ptr);
		this->objects.erase(ptr);
	}
	else{
		throw PointerAccessViolation(ptr, "Pointer");
	}
}

std::vector<std::uint64_t> & ltn::Heap::accessArray(std::uint64_t ptr) {
	if(ptr == 0) {
		throw NullptrViolation();
	}
	if(this->objects.contains(ptr)){
		return std::get<std::vector<std::uint64_t>>(this->objects.at(ptr).data);
	}
	else{
		throw PointerAccessViolation(ptr, "Array");
	}
}

std::string & ltn::Heap::accessString(std::uint64_t ptr) {
	if(ptr == 0) {
		throw NullptrViolation();
	}
	if(this->objects.contains(ptr)){
		return std::get<std::string>(this->objects.at(ptr).data);
	}
	else{
		throw PointerAccessViolation(ptr, "String");
	}
}

bool ltn::Heap::exists(std::uint64_t ptr) const {
	return this->objects.contains(ptr);
}