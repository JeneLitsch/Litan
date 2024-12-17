#pragma once
#include "ltnc/link/LinkInfo.hxx"
#include "ltnc/sst/SST.hxx"
#include "ltnc/inst/inst.hxx"

namespace ltn::c {
	LinkInfo link(const sst::Program & program, const std::vector<inst::Inst> & instructions);
}