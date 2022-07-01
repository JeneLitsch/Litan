#pragma once
#include <array>
#include <string_view>
using namespace std::string_view_literals;
namespace ltn::c::build_in {
	const auto math_min = std::to_array<Instruction>({
		Min{},
		Return{},
	});
	
	const auto math_max = std::to_array<Instruction>({
		Max{},
		Return {},
	});
	
	const auto math_clamp = std::to_array<Instruction>({
		Makevar{},
		Write0{},
		Max{},
		Read0{},
		Min{},
		Return{},
	});

	const auto math_round = std::to_array<Instruction>({
		Round{},
		Return{},
	});
	
	const auto math_floor = std::to_array<Instruction>({
		Floor{},
		Return{},
	});
	
	const auto math_ceil = std::to_array<Instruction>({
		Ceil{},
		Return{},
	});

	const auto math_abs = std::to_array<Instruction>({
		Abs{},
		Return{},
	});
	
	const auto math_hypot = std::to_array<Instruction>({
		Hypot{},
		Return{},
	});
	
	const auto math_sqrt = std::to_array<Instruction>({
		Sqrt{},
		Return{},
	});
	
	const auto math_log = std::to_array<Instruction>({
		Log{},
		Return{},
	});
	
	const auto math_ld = std::to_array<Instruction>({
		Newf{2.0},
		Log{},
		Return{},
	});
	
	const auto math_lg = std::to_array<Instruction>({
		Newf{10.0},
		Log{},
		Return{},
	});

	const auto math_ln = std::to_array<Instruction>({
		Ln{},
		Return{},
	});
	
	const auto math_pow = std::to_array<Instruction>({
		Pow{},
		Return{},
	});

	const auto math_sin = std::to_array<Instruction>({
		Sin{},
		Return{},
	});
	
	const auto math_cos = std::to_array<Instruction>({
		Cos{},
		Return{},
	});
	
	const auto math_tan = std::to_array<Instruction>({
		Tan{},
		Return{},
	});
}