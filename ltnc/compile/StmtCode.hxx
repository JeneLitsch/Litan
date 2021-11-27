#pragma once
#include <string>
namespace ltn::c::compile {
	struct StmtCode {
	public:
		StmtCode(
			const std::string & code,
			std::size_t varCount,
			bool directAllocation = false)
			: 	code(code),
				varCount(varCount),
				directAllocation(directAllocation) {}
		std::string code;
		std::size_t varCount = 0;
		bool directAllocation = false;
	};
}