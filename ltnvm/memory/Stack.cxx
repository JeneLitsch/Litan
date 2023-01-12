#include "Stack.hxx"


namespace ltn::vm {
	Stack::Stack() {
		this->reset();
	}
	void Stack::push_frame(std::uint64_t jumpBack) {
		this->frames.push_back(Frame{
			.return_jump = jumpBack,
			.prev_frame_pointer = this->frame_pointer,
			.except_jump = 0,
			.reg_size = 0,
		});
		this->frame_pointer = this->stack.size();
	}


	std::uint64_t Stack::pop_frame() {
		const auto & frame = this->frames.back();
		const std::uint64_t jumpBack 		 = frame.return_jump;
		const std::uint64_t oldframe_pointer = frame.prev_frame_pointer;
		this->stack.resize(this->frame_pointer);
		this->frame_pointer = oldframe_pointer;
		this->frames.pop_back();
		return jumpBack;
	}


	const std::vector<Value> & Stack::get_container() const {
		return this->stack;
	}

	void Stack::reset() {
		this->stack.clear();
		this->frames.clear();
		this->frame_pointer = 0;
	}

	std::size_t Stack::size() const {
		return this->stack.size();
	}

	std::uint64_t Stack::depth() const {
		return this->frames.size();
	}

	std::uint64_t Stack::get_except_handler() const {
		return this->frames.back().except_jump;
	}

	void Stack::set_except_handler(std::uint64_t addr) {
		this->frames.back().except_jump = addr;
	}

	std::uint64_t Stack::get_regsize() const {
		return this->frames.back().reg_size;
	}

	void Stack::set_regsize(std::uint64_t size) {
		this->frames.back().reg_size = size;
	}
}

