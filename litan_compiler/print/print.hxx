#pragma once
#include <span>
#include "litan_compiler/inst/inst.hxx"

namespace ltn::c {
	std::string print(const std::span<const inst::Inst> & instructions);
}