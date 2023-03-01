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
			const std::size_t address = this->frame_pointer + offset;
			return this->values[address];
		}



		inline void write(std::uint64_t offset, Value value) {
			const std::size_t address = this->frame_pointer + offset;
			this->values[address] = value;
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
		
		const std::uint8_t * pop_frame();
		void push_frame(const std::uint8_t * jumpBack, std::uint8_t arity);	

		const std::uint8_t * get_except_handler() const;
		void set_except_handler(const std::uint8_t * address);
		
		std::uint64_t size() const;
		std::uint64_t depth() const;
		
		const std::vector<Value> & get_values() const;

	private:
		struct Frame {
			const std::uint8_t * return_addr;
			std::uint64_t prev_frame_pointer;
			const std::uint8_t * except_jump = nullptr;
		};

		std::vector<Value> values;
		std::vector<Frame> frames;
		std::uint64_t frame_pointer = 0;
	};
}