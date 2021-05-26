#pragma once
#include <vector>
#include <cstdint>
namespace ltn{
	class ByteCode {
	public:
		ByteCode(const std::vector<std::uint64_t> & instructions) : instructions(instructions) {}
		inline const std::vector<std::uint64_t> & getInstructions() const {
			return this->instructions;
		}
	private:
		std::vector<std::uint64_t> instructions;
	};
}