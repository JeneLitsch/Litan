#pragma once
#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include "Value.hxx"
#include "litan_core/file/FunctionPool.hxx"

namespace ltn::vm {
	class VMStack {
	public:
		struct Frame {
			const std::uint8_t * return_addr;
			std::uint64_t prev_frame_pointer;
			const std::uint8_t * except_jump = nullptr;
			const ltn::FunctionContext * context;
		};



		VMStack();



		inline Value read(std::uint64_t offset) const {
			const std::size_t address = this->frame_pointer + offset;
			return this->values[address];
		}



		inline void write(std::uint64_t offset, Value value) {
			const std::size_t address = this->frame_pointer + offset;
			this->values[address] = value;
		}



		inline Value read_absolute(std::uint64_t address) const {
			return this->values[address];
		}



		inline void write_absolute(std::uint64_t address, Value value) {
			this->values[address] = value;
		}
		


		inline void push(const Value value) {
			this->values.push_back(value);
		}



		inline Value pop() {
			const auto value = this->values.back();
			this->values.pop_back();
			return value;
		}



		template<std::uint64_t N>
		inline std::array<Value, N> pop_n() {
			std::array<Value, N> segment;
			std::copy_n(std::end(values) - N, N, std::begin(segment));
			values.resize(values.size() - N);
			return segment;
		}



		inline const Value peek() const {
			return this->values.back();
		}



		void reset();
		
		const std::uint8_t * pop_frame();
		void push_frame(const std::uint8_t * jumpBack, std::uint64_t arity, const FunctionContext * entry);
		const Frame & get_current_frame() const;

		const std::uint8_t * get_except_handler() const;
		void set_except_handler(const std::uint8_t * address);
		
		std::uint64_t size() const;
		std::uint64_t depth() const;
		
		const std::vector<Value> & get_values() const;

		std::vector<Value> copy_locals() const {
			return std::vector<Value>{
				std::begin(this->values) + static_cast<std::ptrdiff_t>(frame_pointer),
				std::end(this->values),
			};
		}

	private:


		std::vector<Value> values;
		std::vector<Frame> frames;
		std::uint64_t frame_pointer = 0;
	};
}