#pragma once

#include "ltnc/Ltnc.hxx"
#include "ltnvm/VM.hxx"

namespace ltn {
	using VM = vm::VM;
	using Value = vm::Value;

	std::vector<std::uint8_t> build(
		const std::vector<ltn::c::Source> & sources,
		const std::vector<ltn::c::CustomLiteral> & literals = {});
}