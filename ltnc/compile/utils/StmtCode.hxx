#pragma once
#include <string>
#include "InstructionBuffer.hxx"
namespace ltn::c {
	struct StmtCode {
	public:
		StmtCode(
			const InstructionBuffer & code,
			std::size_t var_count,
			bool direct_allocation = false)
			: 	code(code),
				var_count(var_count),
				direct_allocation(direct_allocation) {}
		InstructionBuffer code;
		std::size_t var_count = 0;
		bool direct_allocation = false;
	};
}