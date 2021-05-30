#pragma once
#include <cstdint>
#include <array>
#include <vector>
namespace ltn {
	class StackFrame {
	public:
		StackFrame();
		StackFrame(std::uint64_t jumpback);

		std::uint64_t jumpback;
		std::vector<std::uint64_t> memoryBlock;
	};
}
