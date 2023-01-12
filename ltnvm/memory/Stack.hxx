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

		void push_frame(std::uint64_t jumpBack, std::uint8_t arity);	
		std::uint64_t pop_frame();
		const std::vector<Value> & get_container() const;
		void reset();
		std::size_t size() const;
		std::uint64_t depth() const;

		std::uint64_t get_except_handler() const;
		void set_except_handler(std::uint64_t addr);
		std::uint64_t get_regsize() const;
		void set_regsize(std::uint64_t size);


		inline Value pop()  {
			const auto value = this->stack.back();
			this->stack.pop_back();
			return value;
		}

		inline void remove(std::uint64_t count)  {
			this->stack.resize(this->stack.size() - count);
		}

		inline void resize(std::uint64_t count)  {
			this->stack.resize(count);
		}

		inline const Value peek() const {
			return this->stack.back();
		}
		
		auto peek(std::uint64_t count) {
			auto begin = this->stack.end() - static_cast<std::int64_t>(count);
			auto end = this->stack.end();
			return std::make_pair(begin, end);
		}

		inline void push(const Value value) {
			this->stack.push_back(value);
		}
	private:
		struct Frame {
			std::uint64_t return_addr;
			std::uint64_t prev_frame_pointer;
			std::uint64_t except_jump = 0;
			std::uint64_t reg_size = 0;
		};

		std::vector<Value> stack;
		std::vector<Frame> frames;
		std::uint64_t frame_pointer = 0;
	};
}