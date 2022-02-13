#include "Stack.hxx"
#include "Float.hxx"


namespace ltn::vm {
	Stack::Stack() {
		this->reset();
	}
	void Stack::pushFrame(std::uint64_t jumpBack) {
		this->depthCounter++;
		const std::uint64_t newFramePointer = this->stack.size();
		this->stack.push_back(Value{jumpBack, Value::Type::NVLL});
		this->stack.push_back(Value{this->framePointer, Value::Type::NVLL});
		this->stack.push_back(Value{0, Value::Type::NVLL});
		this->stack.push_back(Value{0, Value::Type::NVLL});
		this->framePointer = newFramePointer;
	}


	std::uint64_t Stack::popFrame() {
		this->depthCounter--;
		const std::uint64_t jumpBack 		= this->stack[this->framePointer + 0].u;
		const std::uint64_t oldFramePointer = this->stack[this->framePointer + 1].u;
		this->stack.resize(this->framePointer);
		this->framePointer = oldFramePointer;
		return jumpBack;
	}


	const std::vector<Value> & Stack::getContainer() const {
		return this->stack;
	}

	void Stack::reset() {
		this->stack.clear();
		this->framePointer = 0;
		this->depthCounter = 0;
	}

	std::size_t Stack::size() const {
		return this->stack.size();
	}

	std::uint64_t Stack::depth() const {
		return this->depthCounter;
	}

	std::uint64_t Stack::getExceptHandler() const {
		const std::size_t addr = this->framePointer + EXCEPT_OFFSET;
		return this->stack[addr].u;
	}

	void Stack::setExceptHandler(std::uint64_t addr) {
		const std::size_t index = this->framePointer + EXCEPT_OFFSET;
		this->stack[index].u = addr;
	}

	std::uint64_t Stack::getRegSize() const {
		const std::size_t addr = this->framePointer + REG_SIZE_OFFSET;
		return this->stack[addr].u;
	}

	void Stack::setRegSize(std::uint64_t size) {
		const std::size_t index = this->framePointer + REG_SIZE_OFFSET;
		this->stack[index].u = size;
	}
}

