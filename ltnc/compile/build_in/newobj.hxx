#pragma once
#include <array>
#include <string_view>
using namespace std::string_view_literals;
namespace ltn::c::compile::build_in {
	const auto queue = std::to_array<Instruction>({
		Newqueue{}, 
		Return{},
	});

	const auto stack = std::to_array<Instruction>({
		Newstack{}, 
		Return{},
	});

	const auto map = std::to_array<Instruction>({
		Newmap{}, 
		Return{},
	});

	const auto array = std::to_array<Instruction>({
		Newarr{0}, 
		Return{},
	});

	const auto range = std::to_array<Instruction>({
		Newrange{}, 
		Return{},
	});

	const auto struc1 = std::to_array<Instruction>({
		Newstruct{}, 
		Return{},
	});
}