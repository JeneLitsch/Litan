#pragma once
#include <string>
namespace ltn::c::compile {
	struct StmtCode {
	public:
		StmtCode(
			const std::string & code,
			std::size_t var_count,
			bool direct_allocation = false)
			: 	code(code),
				var_count(var_count),
				direct_allocation(direct_allocation) {}
		std::string code;
		std::size_t var_count = 0;
		bool direct_allocation = false;
	};
}