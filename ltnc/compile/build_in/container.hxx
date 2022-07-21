#pragma once
#include <array>
#include "ltnc/inst/instructions.hxx"
using namespace ltn::inst;
namespace ltn::c::build_in {
	const auto container_push = std::to_array<Instruction>({
		Push{},
	});

	const auto container_pop = std::to_array<Instruction>({
		Pop{},
		Return{},
	});

	const auto container_peek = std::to_array<Instruction>({
		Peek{},
		Return{},
	});

	const auto container_contains = std::to_array<Instruction>({
		Contains{},
		Return{},
	});

	const auto container_size = std::to_array<Instruction>({
		Size{},
		Return{},
	});

	const auto container_empty = std::to_array<Instruction>({
		Size{},
		Not{},
		Return{},
	});

	const auto container_at = std::to_array<Instruction>({
		At{},
		Return{},
	});
	
	const auto container_front = std::to_array<Instruction>({
		Front{},
		Return{},
	});
	
	const auto container_back = std::to_array<Instruction>({
		Back{},
		Return{},
	});

	const auto container_begin = std::to_array<Instruction>({
		Begin{},
		Return{},
	});

	const auto container_end = std::to_array<Instruction>({
		End{},
		Return{},
	});

	const auto container_insert_back = std::to_array<Instruction>({
		Insert{2},
	});


	const auto container_insert_front = std::to_array<Instruction>({
		Insert{0},
	});

	const auto container_insert = std::to_array<Instruction>({
		Insert{1},
	});

	const auto container_remove_back = std::to_array<Instruction>({
		Remove{2},
	});

	const auto container_remove_front = std::to_array<Instruction>({
		Remove{0},
	});
	
	const auto container_remove = std::to_array<Instruction>({
		Remove{1},
	});
}