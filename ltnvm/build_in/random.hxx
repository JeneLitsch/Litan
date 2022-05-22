#pragma once
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::build_in {
	void split(VmCore & core);
	void rand(VmCore & core);
	void rand_int(VmCore & core);
	void rand_float(VmCore & core);
}