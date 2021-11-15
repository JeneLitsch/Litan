#pragma once
#include <vector>
#include <cstdint>

namespace ltn::vm {
	class Stack {
	public:
		std::uint64_t readU(std::uint64_t offset) const;
		std::int64_t readI(std::uint64_t offset) const;
		double readF(std::uint64_t offset) const;

		void writeU(std::uint64_t offset, std::uint64_t value);
		void writeI(std::uint64_t offset, std::int64_t value);
		void writeF(std::uint64_t offset, double value);

		void pushFrame(std::uint64_t localAlloc, std::uint64_t jumpBack);	
		std::uint64_t popFrame();
	private:

		std::vector<std::uint64_t> stack;
		std::size_t framePointer = 0;
	};
}