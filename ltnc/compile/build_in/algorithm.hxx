#pragma once
#include <array>
#include "ltn/InstructionSet.hxx"
using namespace ltn::inst;
namespace ltn::c::compile::build_in {
	const auto algorithm_sort_ascn = std::to_array<Instruction>({
		BuildIn{ args::Uint16{0x00} },
		Return{},
	});

	const auto algorithm_sort_desc = std::to_array<Instruction>({
		BuildIn{0x01},
		Return{},
	});

	const auto algorithm_is_sorted_ascn = std::to_array<Instruction>({
		BuildIn{0x02},
		Return{},
	});

	const auto algorithm_is_sorted_desc = std::to_array<Instruction>({
		BuildIn{0x03},
		Return{},
	});

	const auto algorithm_find = std::to_array<Instruction>({
		BuildIn{0x04},
		Return{},
	});

	const auto algorithm_copy_front = std::to_array<Instruction>({
		BuildIn{0x05},
		Return{},
	});

	const auto algorithm_copy_back = std::to_array<Instruction>({
		BuildIn{0x06},
		Return{},
	});

	const auto algorithm_fill = std::to_array<Instruction>({
		BuildIn{0x07},
		Return{},
	});

	const auto algorithm_reverse = std::to_array<Instruction>({
		BuildIn{0x08},
		Return{},
	});
}