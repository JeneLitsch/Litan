#pragma once

#include "ltnc/Ltnc.hxx"
#include "ltnvm/LtnVM.hxx"

namespace ltn {
	using LtnVm = vm::LtnVM;

	using Value = vm::Value;

	std::vector<std::uint8_t> build(const std::vector<ltn::c::Source> & sources);
}