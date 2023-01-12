#include "Stack.hxx"


namespace ltn::vm {
	Stack::Stack() {
		this->reset();
	}



	void Stack::push_frame(std::uint64_t return_addr, std::uint8_t arity) {
		this->frames.push_back(Frame{
			.return_addr = return_addr,
			.prev_frame_pointer = this->frame_pointer,
			.except_jump = 0,
		});
		this->frame_pointer = this->values.size() - arity;
	}



	std::uint64_t Stack::pop_frame() {
		const auto & frame = this->frames.back();
		const auto return_addr = frame.return_addr;
		const auto oldframe_pointer = frame.prev_frame_pointer;
		this->values.resize(this->frame_pointer);
		this->frame_pointer = oldframe_pointer;
		this->frames.pop_back();
		return return_addr;
	}



	const std::vector<Value> & Stack::get_values() const {
		return this->values;
	}



	void Stack::reset() {
		this->values.clear();
		this->frames.clear();
		this->frame_pointer = 0;
	}



	std::uint64_t Stack::size() const {
		return this->values.size();
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
}

