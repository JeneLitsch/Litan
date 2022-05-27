#pragma once
#include <array>
#include "ltn/InstructionSet.hxx"
using namespace ltn::inst;
namespace ltn::c::compile::build_in {
	const auto type_typeid = std::to_array<Instruction>({
		TypeId{}, 
		Return{},
	});

	const auto type_clone = std::to_array<Instruction>({
		Clone{}, 
		Return{},
	});
}