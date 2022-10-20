#pragma once
#include <string>
#include "InstructionBuffer.hxx"
namespace ltn::c {
	struct StmtResult {
		InstructionBuffer code;
		std::size_t var_count = 0;
		bool direct_allocation = false;
	};
}