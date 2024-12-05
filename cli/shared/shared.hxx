#pragma once
#include <vector>
#include "ltnc/Ltnc.hxx"

ltn::c::sst::Program analysis_phase(std::string_view script_path);
std::vector<ltn::c::inst::Inst> synthesis_phase(const ltn::c::sst::Program & sst);