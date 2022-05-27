#pragma once
#include <array>
#include "ltn/InstructionSet.hxx"
using namespace ltn::inst;
namespace ltn::c::compile::build_in {
	const auto io_cout = std::to_array<Instruction>({
		Newout{0},
		Return{},
	});

	const auto io_fout = std::to_array<Instruction>({
		Newout{1},
		Return{},
	});

	const auto io_strout = std::to_array<Instruction>({
		Newout{2},
		Return{},
	});

	const auto io_print = std::to_array<Instruction>({
		Out{},
	});


	const auto io_fg_color = std::to_array<Instruction>({
		Stylize{0},
	});


	const auto io_bg_color = std::to_array<Instruction>({
		Stylize{1},
	});


	const auto io_reset_color = std::to_array<Instruction>({
		Stylize{2},
	});


	const auto io_cin = std::to_array<Instruction>({
		Newin{0},
		Return{},
	});

	const auto io_fin = std::to_array<Instruction>({
		Newin{1},
		Return{},
	});

	const auto io_strin = std::to_array<Instruction>({
		Newin{2},
		Return{},
	});

	const auto io_read = std::to_array<Instruction>({
		InStr{},
		Return{},
	});

	const auto io_read_str = std::to_array<Instruction>({
		InStr{},
		Return{},
	});

	const auto io_readln = std::to_array<Instruction>({
		InLine{},
		Return{},
	});

	const auto io_read_bool = std::to_array<Instruction>({
		InBool{},
		Return{},
	});

	const auto io_read_char = std::to_array<Instruction>({
		InChar{},
		Return{},
	});

	const auto io_read_int = std::to_array<Instruction>({
		InInt{},
		Return{},
	});

	const auto io_read_float = std::to_array<Instruction>({
		InFloat{},
		Return{},
	});

	const auto io_read_all = std::to_array<Instruction>({
		InAll{},
		Return{},
	});

	const auto io_is_eof = std::to_array<Instruction>({
		IsEof{},
		Return{},
	});

	const auto io_is_good = std::to_array<Instruction>({
		IsGood{},
		Return{},
	});

	const auto io_close = std::to_array<Instruction>({
		CloseStream{},
		Return{}
	});
}