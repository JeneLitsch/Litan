#pragma once
#include <unordered_map>
#include <string>
#include <cstdint>
#include "ltnc/inst/inst.hxx"
#include "ltnc/AddressTable.hxx"

namespace ltn::c {

	AddressTable scan(const std::vector<inst::Inst> & instructions);
}