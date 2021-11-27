#pragma once
#include <string>
namespace ltn::c::compile {
	struct StmtCode {
	public:
		StmtCode(const std::string & code, std::size_t varCount)
			: code(code), varCount(varCount) {}
		std::string code;
		std::size_t varCount = 0;
	};
}