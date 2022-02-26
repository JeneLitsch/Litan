#include "Stack.hxx"
#include "Float.hxx"


namespace ltn::vm {
	Stack::Stack() {
		this->reset();
	}
	void Stack::push_frame(std::uint64_t jumpBack) {
		this->depth_counter++;
		const std::uint64_t newframe_pointer = this->stack.size();
		this->stack.push_back(Value{jumpBack, Value::Type::NVLL});
		this->stack.push_back(Value{this->frame_pointer, Value::Type::NVLL});
		this->stack.push_back(Value{0, Value::Type::NVLL});
		this->stack.push_back(Value{0, Value::Type::NVLL});
		this->frame_pointer = newframe_pointer;
	}


	std::uint64_t Stack::pop_frame() {
		this->depth_counter--;
		const std::uint64_t jumpBack 		= this->stack[this->frame_pointer + 0].u;
		const std::uint64_t oldframe_pointer = this->stack[this->frame_pointer + 1].u;
		this->stack.resize(this->frame_pointer);
		this->frame_pointer = oldframe_pointer;
		return jumpBack;
	}


	const std::vector<Value> & Stack::get_container() const {
		return this->stack;
	}

	void Stack::reset() {
		this->stack.clear();
		this->frame_pointer = 0;
		this->depth_counter = 0;
	}

	std::size_t Stack::size() const {
		return this->stack.size();
	}

	std::uint64_t Stack::depth() const {
		return this->depth_counter;
	}

	std::uint64_t Stack::get_except_handler() const {
		const std::size_t addr = this->frame_pointer + EXCEPT_OFFSET;
		return this->stack[addr].u;
	}

	void Stack::set_except_handler(std::uint64_t addr) {
		const std::size_t index = this->frame_pointer + EXCEPT_OFFSET;
		this->stack[index].u = addr;
	}

	std::uint64_t Stack::get_regsize() const {
		const std::size_t addr = this->frame_pointer + REG_SIZE_OFFSET;
		return this->stack[addr].u;
	}

	void Stack::set_regsize(std::uint64_t size) {
		const std::size_t index = this->frame_pointer + REG_SIZE_OFFSET;
		this->stack[index].u = size;
	}
}

