#pragma once
#include <array>
#include "ltn/InstructionSet.hxx"
using namespace ltn::inst;
namespace ltn::c::build_in {
	const auto debug_state = std::to_array<Instruction>({
		State{},
		Return{},
	});
}