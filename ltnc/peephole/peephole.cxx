#include "peephole.hxx"
#include "../compile/utils/InstructionBuffer.hxx"

namespace ltn::c {
	std::vector<ltn::inst::Instruction> peephole(
		const std::vector<ltn::inst::Instruction> & input) {
		InstructionBuffer final_buf;
		InstructionBuffer temp_buf;
		for(const auto & inst : input) {
			final_buf << inst;
		}
		return final_buf.get();
	}
}