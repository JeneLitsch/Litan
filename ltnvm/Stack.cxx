#include "Stack.hxx"
#include "Float.hxx"

namespace {
	constexpr std::size_t BASE_OFFSET = 2;
}

std::uint64_t ltn::vm::Stack::readU(std::uint64_t offset) const {
	const std::size_t addr = this->framePointer + BASE_OFFSET + offset;
	return this->stack[addr];
}
std::int64_t ltn::vm::Stack::readI(std::uint64_t offset) const {
	return static_cast<std::int64_t>(this->readU(offset));
}
double ltn::vm::Stack::readF(std::uint64_t offset) const {
	return toFloat(this->readU(offset));
}

void ltn::vm::Stack::writeU(std::uint64_t offset, std::uint64_t value) {
	const std::size_t addr = this->framePointer + BASE_OFFSET + offset;
	this->stack[addr] = value;
}
void ltn::vm::Stack::writeI(std::uint64_t offset, std::int64_t value) {
	this->writeU(offset, static_cast<std::uint64_t>(value));
}
void ltn::vm::Stack::writeF(std::uint64_t offset, double value) {
	this->writeU(offset, toUint(value));
}



void ltn::vm::Stack::pushFrame(std::uint64_t localAlloc, std::uint64_t jumpBack) {
	const std::uint64_t newFramePointer = this->stack.size();
	this->stack.push_back(jumpBack);
	this->stack.push_back(this->framePointer);
	this->framePointer = newFramePointer;
	this->stack.resize(this->stack.size() + localAlloc, 0);
}
std::uint64_t ltn::vm::Stack::popFrame() {
	const std::uint64_t jumpBack 		= this->stack[this->framePointer + 0];
	const std::uint64_t oldFramePointer = this->stack[this->framePointer + 1];
	this->stack.resize(this->framePointer);
	this->framePointer = oldFramePointer;
	return jumpBack;
}

