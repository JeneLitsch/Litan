#pragma once
#include <vector>
#include <cstdint>
#include "Value.hxx"
namespace ltn::vm {
	class Stack {
	public:
		Stack();

		inline Value read(std::uint64_t offset) const {
			const std::size_t addr = this->frame_pointer + offset;
			return this->stack[addr];
		}

		inline void write(std::uint64_t offset, Value value) {
			const std::size_t addr = this->frame_pointer + offset;
			this->stack[addr] = value;
		}
		
		inline void make_var() {
			this->stack.push_back(Value{0U, Value::Type::NVLL});
		}

		inline void make_var(Value value) {
			this->stack.push_back(value);
		}

		void push_frame(std::uint64_t jumpBack);	
		std::uint64_t pop_frame();
		const std::vector<Value> & get_container() const;
		void reset();
		std::size_t size() const;
		std::uint64_t depth() const;

		std::uint64_t get_except_handler() const;
		void set_except_handler(std::uint64_t addr);
		std::uint64_t get_regsize() const;
		void set_regsize(std::uint64_t size);
	private:
		struct Frame {
			std::uint64_t return_jump;
			std::uint64_t prev_frame_pointer;
			std::uint64_t except_jump = 0;
			std::uint64_t reg_size = 0;
		};

		std::vector<Value> stack;
		std::vector<Frame> frames;
		std::uint64_t frame_pointer = 0;
	};
}