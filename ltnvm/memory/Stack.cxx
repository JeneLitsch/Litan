#include "Stack.hxx"
#include "Float.hxx"

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

const std::vector<ltn::vm::Value> & ltn::vm::Stack::getContainer() const {
	return this->stack;
}

void ltn::vm::Stack::reset() {
	this->stack.clear();
	this->framePointer = 0;
}

std::size_t ltn::vm::Stack::size() const {
	return this->stack.size();
}

