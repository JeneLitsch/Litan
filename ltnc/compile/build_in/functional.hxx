#pragma once
#include <array>
#include "ltn/InstructionSet.hxx"
using namespace ltn::inst;
namespace ltn::c::compile::build_in {
	const auto functional_invoke_2 = std::to_array<Instruction>({
		Invoke{},
		Return{},
	});

	const auto functional_invoke_1 = std::to_array<Instruction>({
		Newarr{0},
		Invoke{},
		Return{},
	});

	const auto functional_external = std::to_array<Instruction>({
		External{},
		Return{},
	});
}