#pragma once
#include "ltnvm/VMCore.hxx"

namespace ltn::vm::build_in {
	Value json_load(VMCore & core);
	Value json_store(VMCore & core);
}