#pragma once

#include "ltnc/Ltnc.hxx"
#include "ltnvm/LtnVM.hxx"

namespace ltn {
	using LtnVm = vm::LtnVM;

	using Value = vm::Value;
	using External = vm::ext::External;
	using Api = vm::ext::Api;

	std::vector<std::uint8_t> build(const std::vector<ltn::c::Source> & sources);
}