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
			const std::size_t addr = this->framePointer + BASE_OFFSET + offset;
			return this->stack[addr];
		}

		inline void write(std::uint64_t offset, Value value) {
			const std::size_t addr = this->framePointer + BASE_OFFSET + offset;
			this->stack[addr] = value;
		}
		
		inline void makeVar() {
			this->stack.push_back(Value{0U, Value::Type::NVLL});
		}

		inline void makeVar(Value value) {
			this->stack.push_back(value);
		}

		void pushFrame(std::uint64_t jumpBack);	
		std::uint64_t popFrame();
		const std::vector<Value> & getContainer() const;
		void reset();
		std::size_t size() const;
		std::uint64_t depth() const;

		std::uint64_t getExceptHandler() const;
		void setExceptHandler(std::uint64_t addr);
		std::uint64_t getRegSize() const;
		void setRegSize(std::uint64_t size);
	private:
		std::vector<Value> stack;
		std::uint64_t framePointer;
		std::uint64_t depthCounter;
	};
}