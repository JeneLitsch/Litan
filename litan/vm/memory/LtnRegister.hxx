#pragma once
#include <cstdint>
#include <array>
#include <iterator>
#include "LtnFloat.hxx"
#include "LtnRegisterUnderflow.hxx"
#include "LtnRegisterOverflow.hxx"
namespace ltn{
	class Register {
	public:

		inline std::uint64_t & top() {
			return *(this->current-1);
		}
		
		inline std::uint64_t size() const {
			return static_cast<std::uint64_t>(std::distance(start, current));
		}

		inline void reset() {
			this->start = this->stack.data();
			this->current = start;
		}



		inline std::int64_t popI() {
			return static_cast<std::int64_t>(this->pop());
		}
		
		inline std::uint64_t popU() {
			return this->pop();
		}
		
		inline double popF() {
			return Float::uintToDouble(this->pop());
		}



		inline void push(const std::int64_t val) {
			this->push(static_cast<std::uint64_t>(val));
		}

		inline void push(const bool val) {
			this->push(static_cast<std::uint64_t>(val));
		}

		inline void push(const double val) {
			this->push(Float::doubleToUint(val));
		}

		inline void push(const std::uint64_t value) {
			if(this->size() >= 256) {
				throw RegisterOverflow();
			}
			*current = value;
			this->current++; 
		}

		// const std::stack<std::uint64_t> & getStack() const;
	private:

		inline std::uint64_t pop() {
			if(this->size() == 0) {
				throw RegisterUnderflow();
			}
			std::uint64_t value = this->top();
			this->current--;
			return value;
		}
		std::uint64_t * current;
		std::uint64_t * start;
		std::array<std::uint64_t, 256> stack;
	};
}
