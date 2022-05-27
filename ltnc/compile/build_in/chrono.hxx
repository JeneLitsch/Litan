#pragma once
#include <array>
#include "ltn/InstructionSet.hxx"
using namespace ltn::inst;
namespace ltn::c::compile::build_in {
	const auto chrono_clock = std::to_array<Instruction>({
		Newclock{},
		Return{},
	});

	const auto chrono_to_seconds = std::to_array<Instruction>({
		CastFloat{},
		Return{},
	});

	const auto chrono_to_milliseconds = std::to_array<Instruction>({
		CastFloat{},
		Newf{1000.0},
		Mlt{},
		Return{},
	});
}