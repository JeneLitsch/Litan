#pragma once
#include <string>
namespace ltnc {
	struct StmtInfo {
		StmtInfo(const std::string & code, unsigned stackalloc)
			: code(code), stackalloc(stackalloc)  {}
		
		StmtInfo(const StmtInfo & info) 
			: code(info.code), stackalloc(info.stackalloc) {}
		
		const std::string code;
		const unsigned stackalloc;
	};
}