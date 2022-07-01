#pragma once
#include <array>
#include "ltn/InstructionSet.hxx"
using namespace ltn::inst;
namespace ltn::c::build_in {
	const auto random_mersenne_0 = std::to_array<Instruction>({
		Newrng{00}, 
		Return{},
	});

	const auto random_mersenne_1 = std::to_array<Instruction>({
		Newrng{01}, 
		Return{},
	});
	
	const auto random_split = std::to_array<Instruction>({
		BuildIn{0x10}, 
		Return{},
	});

	const auto random_rand = std::to_array<Instruction>({
		BuildIn{0x11}, 
		Return{},
	});

	const auto random_rand_int = std::to_array<Instruction>({
		BuildIn{0x12}, 
		Return{},
	});

	const auto random_rand_float = std::to_array<Instruction>({
		BuildIn{0x13}, 
		Return{},
	});
}