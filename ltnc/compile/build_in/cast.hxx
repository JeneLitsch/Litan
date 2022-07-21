#pragma once
#include <array>
#include "ltnc/inst/instructions.hxx"
using namespace ltn::inst;

namespace ltn::c::build_in {
	const auto cast_bool = std::to_array<Instruction>({
		CastBool{},
		Return{},
	});
	
	const auto cast_char = std::to_array<Instruction>({
		CastChar{},
		Return{},
	});
	
	const auto cast_int = std::to_array<Instruction>({
		CastInt{},
		Return{},
	});
	
	const auto cast_float = std::to_array<Instruction>({
		CastFloat{},
		Return{},
	});
	
	const auto cast_string = std::to_array<Instruction>({
		CastString{},
		Return{},
	});
	
	const auto cast_array = std::to_array<Instruction>({
		CastArray{},
		Return{},
	});
}