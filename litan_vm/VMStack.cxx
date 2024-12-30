#include "VMStack.hxx"


namespace ltn::vm {
	VMStack::VMStack() {
		this->reset();
	}



	void VMStack::push_frame(const std::uint8_t * return_addr, std::uint64_t arity, const FunctionContext * context) {
		this->frames.push_back(Frame{
			.return_addr = return_addr,
			.prev_frame_pointer = this->frame_pointer,
			.context = context,
		});
		this->frame_pointer = this->values.size() - arity;
		this->values.resize(this->values.size() + context->frame_size, value::null);
	}



	void VMStack::reuse_frame(std::uint64_t arity, const FunctionContext * context) {
		// Move args
		for (std::int64_t i = 0; i < arity; i++) {
			write(i, peek(- arity + i));
		}

		Frame & frame = this->frames.back();
		// Keep prev_frame_pointer
		frame.context = context;
		// this->frame_pointer = this->values.size() - context->arity;
		
		this->values.resize(this->frame_pointer + arity + context->frame_size, value::null);
	}




	const std::uint8_t * VMStack::pop_frame() {
		const auto & frame = this->frames.back();
		const auto return_addr = frame.return_addr;
		const auto oldframe_pointer = frame.prev_frame_pointer;
		this->values.resize(this->frame_pointer);
		this->frame_pointer = oldframe_pointer;
		this->frames.pop_back();
		return return_addr;
	}



	const VMStack::Frame & VMStack::get_current_frame() const {
		return frames.back();
	}



	const std::vector<Value> & VMStack::get_values() const {
		return this->values;
	}



	void VMStack::reset() {
		this->values.clear();
		this->frames.clear();
		this->frame_pointer = 0;
	}



	std::uint64_t VMStack::size() const {
		return this->values.size();
	}



	std::uint64_t VMStack::depth() const {
		return this->frames.size();
	}



	std::uint64_t VMStack::get_except_handler() const {
		return this->frames.back().context->except_handler;
	}



	void VMStack::set_except_handler(std::uint64_t address) {
	}
}

