#pragma once

#include "litan_compiler/inst/inst.hxx"

namespace ltn::c {
	std::vector<inst::Inst> peephole(const std::vector<inst::Inst> & input);
}