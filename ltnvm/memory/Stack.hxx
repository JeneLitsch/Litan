#pragma once
#include <vector>
#include <cstdint>
#include <iostream>
#include "Value.hxx"
namespace ltn::vm {
	class Stack {
	public:
		Stack();



		inline Value read(std::uint64_t offset) const {
			const std::size_t addr = this->frame_pointer + offset;
			return this->values[addr];
		}



		inline void write(std::uint64_t offset, Value value) {
			const std::size_t addr = this->frame_pointer + offset;
			this->values[addr] = value;
		}
		


		inline void push(const Value value) {
			this->values.push_back(value);
		}



		inline void push_null() {
			this->values.push_back(value::null);
		}



		inline Value pop() {
			const auto value = this->values.back();
			this->values.pop_back();
			return value;
		}



		inline const Value peek() const {
			return this->values.back();
		}



		void reset();
		
		std::uint64_t pop_frame();
		void push_frame(std::uint64_t jumpBack, std::uint8_t arity);	

		std::uint64_t get_except_handler() const;
		void set_except_handler(std::uint64_t addr);
		
		std::uint64_t size() const;
		std::uint64_t depth() const;
		
		const std::vector<Value> & get_values() const;

	private:
		struct Frame {
			std::uint64_t return_addr;
			std::uint64_t prev_frame_pointer;
			std::uint64_t except_jump = 0;
		};

		std::vector<Value> values;
		std::vector<Frame> frames;
		std::uint64_t frame_pointer = 0;
	};
}