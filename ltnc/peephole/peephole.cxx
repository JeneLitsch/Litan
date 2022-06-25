#include "peephole.hxx"
#include "../compile/utils/InstructionBuffer.hxx"

namespace ltn::c::peephole {
	std::vector<ltn::inst::Instruction> optimize(
		const std::vector<ltn::inst::Instruction> & input) {
		std::vector<ltn::inst::Instruction> a = input;
		a.push_back(ltn::inst::Add{});
		a.push_back(ltn::inst::Sub{});
		a.push_back(ltn::inst::Newarr{});
		return a;
	}
}