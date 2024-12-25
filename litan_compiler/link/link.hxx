#pragma once
#include "litan_compiler/link/LinkInfo.hxx"
#include "litan_compiler/sst/SST.hxx"
#include "litan_compiler/inst/inst.hxx"

namespace ltn::c {
	LinkInfo link(const sst::Program & program, const std::vector<inst::Inst> & instructions);
}