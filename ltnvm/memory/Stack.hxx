#pragma once
#include <vector>
#include <cstdint>
#include "Value.hxx"
namespace ltn::vm {
	class Stack {
		constexpr static inline std::size_t EXCEPT_OFFSET = 2;
		constexpr static inline std::size_t REG_SIZE_OFFSET = 3;
		constexpr static inline std::size_t BASE_OFFSET = 4;
	public:
		Stack();

		inline Value read(std::uint64_t offset) const {
			const std::size_t addr = this->frame_pointer + BASE_OFFSET + offset;
			return this->stack[addr];
		}

		inline void write(std::uint64_t offset, Value value) {
			const std::size_t addr = this->frame_pointer + BASE_OFFSET + offset;
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
		std::vector<Value> stack;
		std::uint64_t frame_pointer;
		std::uint64_t depth_counter;
	};
}