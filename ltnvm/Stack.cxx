#include "Stack.hxx"
#include "Float.hxx"

namespace {
	constexpr std::size_t BASE_OFFSET = 2;
}

ltn::vm::Value ltn::vm::Stack::read(std::uint64_t offset) const {
	const std::size_t addr = this->framePointer + BASE_OFFSET + offset;
	return this->stack[addr];
}

void ltn::vm::Stack::write(std::uint64_t offset, Value value) {
	const std::size_t addr = this->framePointer + BASE_OFFSET + offset;
	this->stack[addr] = value;
}

void ltn::vm::Stack::makeVar() {
	this->stack.push_back(Value{0U, Value::Type::NVLL});
}

void ltn::vm::Stack::pushFrame(std::uint64_t jumpBack) {
	const std::uint64_t newFramePointer = this->stack.size();
	this->stack.push_back(Value{jumpBack, Value::Type::NVLL});
	this->stack.push_back(Value{this->framePointer, Value::Type::NVLL});
	this->framePointer = newFramePointer;
}
std::uint64_t ltn::vm::Stack::popFrame() {
	const std::uint64_t jumpBack 		= this->stack[this->framePointer + 0].u;
	const std::uint64_t oldFramePointer = this->stack[this->framePointer + 1].u;
	this->stack.resize(this->framePointer);
	this->framePointer = oldFramePointer;
	return jumpBack;
}

